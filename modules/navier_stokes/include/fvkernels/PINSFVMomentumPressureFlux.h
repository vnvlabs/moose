//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVFluxKernel.h"

/**
 * A flux kernel using the divergence theorem for the pressure gradient term in the momentum
 * equation
 */
class PINSFVMomentumPressureFlux : public FVFluxKernel
{
public:
  static InputParameters validParams();
  PINSFVMomentumPressureFlux(const InputParameters & params);

protected:
  ADReal computeQpResidual() override;

  /// the current element porosity
  const VariableValue & _eps;
  /// the neighbor element porosity
  const VariableValue & _eps_neighbor;
  /// the current element pressure
  const ADVariableValue & _p_elem;
  /// the neighbor element pressure
  const ADVariableValue & _p_neighbor;
  /// which momentum component this kernel applies to
  const int _index;
};
