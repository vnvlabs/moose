//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// StochasticTools includes
#include "SamplerFullSolveMultiApp.h"
#include "Sampler.h"
#include "StochasticToolsTransfer.h"

registerMooseObject("StochasticToolsApp", SamplerFullSolveMultiApp);

InputParameters
SamplerFullSolveMultiApp::validParams()
{
  InputParameters params = FullSolveMultiApp::validParams();
  params += SamplerInterface::validParams();
  params.addClassDescription(
      "Creates a full-solve type sub-application for each row of each Sampler matrix.");
  params.addRequiredParam<SamplerName>("sampler",
                                       "The Sampler object to utilize for creating MultiApps.");
  params.suppressParameter<std::vector<Point>>("positions");
  params.suppressParameter<bool>("output_in_position");
  params.suppressParameter<std::vector<FileName>>("positions_file");
  params.suppressParameter<Real>("move_time");
  params.suppressParameter<std::vector<Point>>("move_positions");
  params.suppressParameter<std::vector<unsigned int>>("move_apps");
  params.set<bool>("use_positions") = false;

  MooseEnum modes("normal=0 batch-reset=1 batch-restore=2", "normal");
  params.addParam<MooseEnum>(
      "mode",
      modes,
      "The operation mode, 'normal' creates one sub-application for each row in the Sampler and "
      "'batch' creates one sub-application for each processor and re-executes for each row.");
  return params;
}

SamplerFullSolveMultiApp::SamplerFullSolveMultiApp(const InputParameters & parameters)
  : FullSolveMultiApp(parameters),
    SamplerInterface(this),
    _sampler(getSampler("sampler")),
    _mode(getParam<MooseEnum>("mode").getEnum<StochasticTools::MultiAppMode>()),
    _local_batch_app_index(0),
    _solved_once(false)
{
  if (getParam<unsigned int>("min_procs_per_app") !=
          _sampler.getParam<unsigned int>("min_procs_per_row") ||
      getParam<unsigned int>("max_procs_per_app") !=
          _sampler.getParam<unsigned int>("max_procs_per_row"))
    paramError("sampler",
               "Sampler and multiapp communicator configuration inconsistent. Please ensure that "
               "'MultiApps/",
               name(),
               "/min(max)_procs_per_app' and 'Samplers/",
               _sampler.name(),
               "/min(max)_procs_per_row' are the same.");

  init(_sampler.getNumberOfRows(),
       _sampler.getRankConfig(_mode == StochasticTools::MultiAppMode::BATCH_RESET ||
                              _mode == StochasticTools::MultiAppMode::BATCH_RESTORE));
  _number_of_sampler_rows = _sampler.getNumberOfRows();
}

void SamplerFullSolveMultiApp::preTransfer(Real /*dt*/, Real /*target_time*/)
{
  // Reinitialize MultiApp size
  const auto num_rows = _sampler.getNumberOfRows();
  if (num_rows != _number_of_sampler_rows)
  {
    init(num_rows,
         _sampler.getRankConfig(_mode == StochasticTools::MultiAppMode::BATCH_RESET ||
                                _mode == StochasticTools::MultiAppMode::BATCH_RESTORE));
    _number_of_sampler_rows = num_rows;
    _row_data.clear();
  }

  // Reinitialize app to original state prior to solve, if a solve has occured
  if (_solved_once)
    initialSetup();
}

bool
SamplerFullSolveMultiApp::solveStep(Real dt, Real target_time, bool auto_advance)
{
  TIME_SECTION("solveStep", 3, "Solving SamplerFullSolveMultiApp");

  mooseAssert(_my_num_apps, _sampler.getNumberOfLocalRows());

  bool last_solve_converged = true;

  if (_mode == StochasticTools::MultiAppMode::BATCH_RESET ||
      _mode == StochasticTools::MultiAppMode::BATCH_RESTORE)
    last_solve_converged = solveStepBatch(dt, target_time, auto_advance);
  else
    last_solve_converged = FullSolveMultiApp::solveStep(dt, target_time, auto_advance);

  _solved_once = true;

  return last_solve_converged;
}

bool
SamplerFullSolveMultiApp::solveStepBatch(Real dt, Real target_time, bool auto_advance)
{
  // Value to return
  bool last_solve_converged = true;

  // List of active relevant Transfer objects
  std::vector<std::shared_ptr<StochasticToolsTransfer>> to_transfers =
      getActiveStochasticToolsTransfers(MultiAppTransfer::TO_MULTIAPP);
  std::vector<std::shared_ptr<StochasticToolsTransfer>> from_transfers =
      getActiveStochasticToolsTransfers(MultiAppTransfer::FROM_MULTIAPP);

  // Initialize to/from transfers
  for (auto transfer : to_transfers)
  {
    transfer->setGlobalMultiAppIndex(_rank_config.first_local_app_index);
    transfer->initializeToMultiapp();
  }
  for (auto transfer : from_transfers)
  {
    transfer->setGlobalMultiAppIndex(_rank_config.first_local_app_index);
    transfer->initializeFromMultiapp();
  }

  if (_mode == StochasticTools::MultiAppMode::BATCH_RESTORE)
    backup();

  // Perform batch MultiApp solves
  _local_batch_app_index = 0;
  for (dof_id_type i = _rank_config.first_local_sim_index;
       i < _rank_config.first_local_sim_index + _rank_config.num_local_sims;
       ++i)
  {
    updateRowData(_local_batch_app_index);

    for (auto & transfer : to_transfers)
    {
      transfer->setGlobalRowIndex(i);
      transfer->setCurrentRow(_row_data);
      transfer->executeToMultiapp();
    }

    last_solve_converged = FullSolveMultiApp::solveStep(dt, target_time, auto_advance);

    for (auto & transfer : from_transfers)
    {
      transfer->setGlobalRowIndex(i);
      transfer->setCurrentRow(_row_data);
      transfer->executeFromMultiapp();
    }

    _local_batch_app_index++;

    if (i < _rank_config.first_local_sim_index + _rank_config.num_local_sims - 1)
    {
      if (_mode == StochasticTools::MultiAppMode::BATCH_RESTORE)
        restore();
      else
      {
        resetApp(_local_batch_app_index + i, target_time);
        initialSetup();
      }
    }
  }
  _local_batch_app_index = 0;

  // Finalize to/from transfers
  for (auto transfer : to_transfers)
    transfer->finalizeToMultiapp();
  for (auto transfer : from_transfers)
    transfer->finalizeFromMultiapp();

  return last_solve_converged;
}

std::vector<std::shared_ptr<StochasticToolsTransfer>>
SamplerFullSolveMultiApp::getActiveStochasticToolsTransfers(Transfer::DIRECTION direction)
{
  std::vector<std::shared_ptr<StochasticToolsTransfer>> output;
  const ExecuteMooseObjectWarehouse<Transfer> & warehouse =
      _fe_problem.getMultiAppTransferWarehouse(direction);
  for (std::shared_ptr<Transfer> transfer : warehouse.getActiveObjects())
  {
    auto ptr = std::dynamic_pointer_cast<StochasticToolsTransfer>(transfer);
    if (ptr && ptr->getMultiApp().get() == this)
      output.push_back(ptr);
  }
  return output;
}

std::string
SamplerFullSolveMultiApp::getCommandLineArgsParamHelper(unsigned int local_app)
{
  std::string args;

  // With multiple processors per app, there are no local rows for non-root processors
  if (isRootProcessor())
  {
    // Since we only store param_names in cli_args, we need to find the values for each param from
    // sampler data and combine them to get full command line option strings.
    updateRowData(_mode == StochasticTools::MultiAppMode::NORMAL ? local_app
                                                                 : _local_batch_app_index);
    const std::vector<std::string> & full_args_name =
        MooseUtils::split(FullSolveMultiApp::getCommandLineArgsParamHelper(local_app), ";");
    args = sampledCommandLineArgs(_row_data, full_args_name);
  }

  _my_communicator.broadcast(args);
  return args;
}

void
SamplerFullSolveMultiApp::updateRowData(dof_id_type local_index)
{
  if (!isRootProcessor())
    return;

  mooseAssert(local_index < _sampler.getNumberOfLocalRows(),
              "Local index must be less than number of local rows.");

  if (_row_data.empty() ||
      (_local_row_index == _sampler.getNumberOfLocalRows() - 1 && local_index == 0))
  {
    mooseAssert(local_index == 0,
                "The first time calling updateRowData must have a local index of 0.");
    _local_row_index = 0;
    _row_data = _sampler.getNextLocalRow();
  }
  else if (local_index - _local_row_index == 1)
  {
    _local_row_index++;
    _row_data = _sampler.getNextLocalRow();
  }

  mooseAssert(local_index == _local_row_index,
              "Local index must be equal or one greater than the index previously called.");
}

std::string
SamplerFullSolveMultiApp::sampledCommandLineArgs(const std::vector<Real> & row,
                                                 const std::vector<std::string> & full_args_name)
{
  std::ostringstream oss;

  // Find parameters that are meant to be assigned by sampler values
  std::vector<std::string> cli_args_name;
  for (const auto & fan : full_args_name)
  {
    // If it has an '=', then it is not meant to be modified
    if (fan.find("=") == std::string::npos)
      cli_args_name.push_back(fan);
    else
      oss << fan << ";";
  }

  // Make sure the parameters either all have brackets, or none of them do
  bool has_brackets = false;
  if (cli_args_name.size())
  {
    has_brackets = cli_args_name[0].find("[") != std::string::npos;
    for (unsigned int i = 1; i < cli_args_name.size(); ++i)
      if (has_brackets != (cli_args_name[i].find("[") != std::string::npos))
        ::mooseError("If the bracket is used, it must be provided to every parameter.");
  }
  if (!has_brackets && cli_args_name.size() && cli_args_name.size() != row.size())
    ::mooseError("Number of command line arguments does not match number of sampler columns.");

  for (unsigned int i = 0; i < cli_args_name.size(); ++i)
  {
    // Assign bracketed parameters
    if (has_brackets)
    {
      // Split param name and vector assignment: "param[0,(3.14),1]" -> {"param", "0,(3.14),1]"}
      const std::vector<std::string> & vector_param = MooseUtils::split(cli_args_name[i], "[");
      // Get inices of vector: "0,(3.14),1]" -> {"0", "(3.14)", "1"}
      const std::vector<std::string> & index_string =
          MooseUtils::split(vector_param[1].substr(0, vector_param[1].find("]")), ",");

      // Loop through indices and assign parameter: param='row[0] 3.14 row[1]'
      oss << vector_param[0] << "='";
      std::string sep = "";
      for (const auto & istr : index_string)
      {
        oss << sep;
        sep = " ";
        // If the value is enclosed in parentheses, then it isn't an index, it's a value
        if (istr.find("(") != std::string::npos)
          oss << std::stod(istr.substr(istr.find("(") + 1));
        // Assign the value from row if it is an index
        else
        {
          unsigned int index = MooseUtils::stringToInteger(istr);
          if (index >= row.size())
            ::mooseError("The provided global column index (",
                         index,
                         ") for ",
                         vector_param[0],
                         " is out of bound.");
          oss << Moose::stringify(row[index]);
        }
      }
      oss << "';";
    }
    // Assign scalar parameters
    else
    {
      oss << cli_args_name[i] << "=" << Moose::stringify(row[i]) << ";";
    }
  }

  return oss.str();
}
