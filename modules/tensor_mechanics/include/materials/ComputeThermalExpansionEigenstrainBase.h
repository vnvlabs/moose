//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ComputeEigenstrainBase.h"
#include "DerivativeMaterialInterface.h"
#include "RankTwoTensorForward.h"

/**
 * ComputeThermalExpansionEigenstrainBase is a base class for all models that
 * compute eigenstrains due to thermal expansion of a material.
 */
template <bool is_ad>
class ComputeThermalExpansionEigenstrainBaseTempl
  : public DerivativeMaterialInterface<ComputeEigenstrainBaseTempl<is_ad>>
{
public:
  static InputParameters validParams();

  ComputeThermalExpansionEigenstrainBaseTempl(const InputParameters & parameters);

protected:
  virtual void computeQpEigenstrain() override;
  /*
   * Compute the total thermal strain relative to the stress-free temperature at
   * the current temperature, as well as the current instantaneous thermal
   * expansion coefficient.
   * param thermal_strain    The current total linear thermal strain
   *                         (\delta L / L)
   * param instantaneous_cte The current instantaneous coefficient of thermal
   *                         expansion (derivative of thermal_strain wrt
   *                         temperature
   */
  virtual void computeThermalStrain(Real & thermal_strain, Real & instantaneous_cte);
  virtual void computeThermalStrain(ADReal & thermal_strain);

  /// lag temperature variable
  const bool _use_old_temperature;

  /// old temperature for use_old_temperature = true
  const VariableValue & _temperature_old;

  /// current temperature
  const GenericVariableValue<is_ad> & _temperature;

  /// the eigenstrain derivative
  typename std::conditional<is_ad, void *, MaterialProperty<RankTwoTensor> &>::type
      _deigenstrain_dT;

  const VariableValue & _stress_free_temperature;

  using ComputeEigenstrainBaseTempl<is_ad>::_qp;
  using ComputeEigenstrainBaseTempl<is_ad>::_eigenstrain;
  using ComputeEigenstrainBaseTempl<is_ad>::_eigenstrain_name;
};

typedef ComputeThermalExpansionEigenstrainBaseTempl<false> ComputeThermalExpansionEigenstrainBase;
typedef ComputeThermalExpansionEigenstrainBaseTempl<true> ADComputeThermalExpansionEigenstrainBase;
