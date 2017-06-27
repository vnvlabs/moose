/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "NonconservedAction.h"

// MOOSE includes
#include "Conversion.h"
#include "FEProblem.h"
#include "Factory.h"
#include "MooseObjectAction.h"
#include "MooseMesh.h"

// libMesh includes
#include "libmesh/string_to_enum.h"

template <>
InputParameters
validParams<NonconservedAction>()
{
  InputParameters params = validParams<Action>();
  params.addClassDescription(
      "Set up the variable and the kernels needed for a nonconserved phase field variable");
  // Get MooseEnums for the possible order/family options for this variable
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());
  params.addParam<MooseEnum>("family",
                             families,
                             "Specifies the family of FE "
                             "shape functions to use for this variable");
  params.addParam<MooseEnum>("order",
                             orders,
                             "Specifies the order of the FE "
                             "shape function to use for this variable");
  params.addParam<Real>("scaling", 1.0, "Specifies a scaling factor to apply to this variable");
  params.addParam<bool>("implicit", true, "Whether kernels are implicit or not");
  params.addParam<bool>(
      "use_displaced_mesh", false, "Whether to use displaced mesh in the kernels");
  params.addParamNamesToGroup("scaling implicit use_displaced_mesh", "Advanced");
  params.addParam<MaterialPropertyName>("mobility", "L", "The mobility used with the kernel");
  params.addParam<std::vector<VariableName>>("args",
                                             "Vector of variable arguments this kernel depends on");
  params.addRequiredParam<MaterialPropertyName>(
      "free_energy", "Base name of the free energy function F defined in a free energy material");
  params.addParam<MaterialPropertyName>("kappa", "kappa_op", "The kappa used with the kernel");
  params.addParam<bool>("variable_mobility",
                        true,
                        "The mobility is a function of any MOOSE variable (if "
                        "this is set to false, L must be constant over the "
                        "entire domain!)");

  return params;
}

NonconservedAction::NonconservedAction(const InputParameters & params)
  : Action(params),
    _var_name(name()),
    _fe_type(Utility::string_to_enum<Order>(getParam<MooseEnum>("order")),
             Utility::string_to_enum<FEFamily>(getParam<MooseEnum>("family")))
{
}

void
NonconservedAction::act()
{
  //
  // Add variable
  //
  if (_current_task == "add_variable")
  {
    // Create nonconserved variable
    _problem->addVariable(_var_name, _fe_type, getParam<Real>("scaling"));
  }

  //
  // Add Kernels
  //
  else if (_current_task == "add_kernel")
  {
    // Add time derivative kernel
    std::string kernel_type = "TimeDerivative";

    std::string kernel_name = _var_name + "_" + kernel_type;
    InputParameters params1 = _factory.getValidParams(kernel_type);
    params1.set<NonlinearVariableName>("variable") = _var_name;
    params1.applyParameters(parameters());

    _problem->addKernel(kernel_type, kernel_name, params1);

    // Add AllenCahn kernel
    kernel_type = "AllenCahn";

    kernel_name = _var_name + "_" + kernel_type;
    InputParameters params2 = _factory.getValidParams(kernel_type);
    params2.set<NonlinearVariableName>("variable") = _var_name;
    params2.set<MaterialPropertyName>("mob_name") = getParam<MaterialPropertyName>("mobility");
    params2.set<MaterialPropertyName>("f_name") = getParam<MaterialPropertyName>("free_energy");
    params2.applyParameters(parameters());

    _problem->addKernel(kernel_type, kernel_name, params2);

    // Add ACInterface kernel
    kernel_type = "ACInterface";

    kernel_name = _var_name + "_" + kernel_type;
    InputParameters params3 = _factory.getValidParams(kernel_type);
    params3.set<NonlinearVariableName>("variable") = _var_name;
    params3.set<MaterialPropertyName>("mob_name") = getParam<MaterialPropertyName>("mobility");
    params3.set<MaterialPropertyName>("kappa_name") = getParam<MaterialPropertyName>("kappa");
    params3.set<bool>("variable_L") = getParam<bool>("variable_mobility");
    params3.applyParameters(parameters());

    _problem->addKernel(kernel_type, kernel_name, params3);
  }
}