//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVTimeKernel.h"

class PINSFVEnergyTimeDerivative : public FVTimeKernel
{
public:
  static InputParameters validParams();
  PINSFVEnergyTimeDerivative(const InputParameters & params);

protected:
  ADReal computeQpResidual() override;

  /// the density
  const Real & _rho;
  /// the heat conductivity
  const ADMaterialProperty<Real> & _cp;
  /// the porosity
  const VariableValue & _eps;
  /// whether this kernel is being used for a solid or a fluid temperature
  const bool _is_solid;
};
