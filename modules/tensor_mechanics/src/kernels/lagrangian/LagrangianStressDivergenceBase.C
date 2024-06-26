//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LagrangianStressDivergenceBase.h"

InputParameters
LagrangianStressDivergenceBase::validParams()
{
  InputParameters params = Kernel::validParams();

  params.addRequiredParam<unsigned int>("component", "Which direction this kernel acts in");
  params.addRequiredCoupledVar("displacements", "The displacement components");

  params.addParam<bool>("large_kinematics", false, "Use large displacement kinematics");
  params.addParam<bool>("stabilize_strain", false, "Average the volumetric strains");

  params.addParam<std::string>("base_name", "Material property base name");

  params.addRequiredRangeCheckedParam<unsigned int>("component",
                                                    "component < 3",
                                                    "An integer corresponding to the direction "
                                                    "the variable this kernel acts in. (0 for x, "
                                                    "1 for y, 2 for z)");
  params.addCoupledVar("temperature",
                       "The name of the temperature variable used in the "
                       "ComputeThermalExpansionEigenstrain.  (Not required for "
                       "simulations without temperature coupling.)");

  params.addParam<std::vector<MaterialPropertyName>>(
      "eigenstrain_names",
      "List of eigenstrains used in the strain calculation. Used for computing their derivatives "
      "for off-diagonal Jacobian terms.");

  return params;
}

LagrangianStressDivergenceBase::LagrangianStressDivergenceBase(const InputParameters & parameters)
  : JvarMapKernelInterface<DerivativeMaterialInterface<Kernel>>(parameters),
    _large_kinematics(getParam<bool>("large_kinematics")),
    _stabilize_strain(getParam<bool>("stabilize_strain")),
    _base_name(isParamValid("base_name") ? getParam<std::string>("base_name") + "_" : ""),
    _component(getParam<unsigned int>("component")),
    _ndisp(coupledComponents("displacements")),
    _disp_nums(_ndisp),
    _temperature(isCoupled("temperature") ? getVar("temperature", 0) : nullptr)
{
  // Do the vector coupling of the displacements
  for (unsigned int i = 0; i < _ndisp; i++)
    _disp_nums[i] = coupled("displacements", i);

  // We need to use identical discretizations for all displacement components
  auto order_x = getVar("displacements", 0)->order();
  for (unsigned int i = 1; i < _ndisp; i++)
  {
    if (getVar("displacements", i)->order() != order_x)
      mooseError("The Lagrangian StressDivergence kernels require equal "
                 "order interpolation for all displacements.");
  }

  // fetch eigenstrain derivatives
  const auto nvar = _coupled_moose_vars.size();
  _deigenstrain_dargs.resize(nvar);
  for (std::size_t i = 0; i < nvar; ++i)
    for (auto eigenstrain_name : getParam<std::vector<MaterialPropertyName>>("eigenstrain_names"))
      _deigenstrain_dargs[i].push_back(&getMaterialPropertyDerivative<RankTwoTensor>(
          eigenstrain_name, _coupled_moose_vars[i]->name()));
}

void
LagrangianStressDivergenceBase::computeResidual()
{
  precalculateResidual();
  Kernel::computeResidual();
}

void
LagrangianStressDivergenceBase::computeJacobian()
{
  precalculateJacobian();
  Kernel::computeJacobian();
}

void
LagrangianStressDivergenceBase::computeOffDiagJacobian(const unsigned int jvar)
{
  precalculateJacobian();
  Kernel::computeOffDiagJacobian(jvar);
}

void
LagrangianStressDivergenceBase::precalculateResidual()
{
  // i.e. do nothing by default
}

void
LagrangianStressDivergenceBase::precalculateJacobian()
{
  // i.e. do nothing by default
}

RankTwoTensor
LagrangianStressDivergenceBase::fullGrad(unsigned int m,
                                         bool use_stable,
                                         const RealGradient & base_grad,
                                         const RealGradient & avg_grad)
{
  // The trick here is for the standard solids formulation you can work
  // with trial function gradient vectors (i.e. don't worry about the
  // other displacement components).  However for the
  // stabilized methods the "trace" term introduces non-zeros on
  // m indices other than the current trial function index...

  // Certain "cross-jacobian" terms, like the updated geometric stiffness
  // work better if you split things out into "stabilized" and "unstabilized"
  // test/trial gradients, hence we have a bool to apply stabilization
  // rather than rely on a property.

  // So this is the base, unstabilized version of the gradient
  // with zeros on the non-m rows

  // Unstabilized first
  RankTwoTensor G = gradOp(m, base_grad);

  // And this adds  stabilization, only if required
  if (use_stable)
    return stabilizeGrad(G, gradOp(m, avg_grad));

  return G;
}

RankTwoTensor
LagrangianStressDivergenceBase::gradOp(unsigned int m, const RealGradient & grad)
{
  RankTwoTensor G;
  for (size_t j = 0; j < _ndisp; j++)
    G(m, j) = grad(j);

  return G;
}
