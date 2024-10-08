//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADHillCreepStressUpdate.h"
#include "ElasticityTensorTools.h"

registerMooseObject("TensorMechanicsApp", ADHillCreepStressUpdate);

InputParameters
ADHillCreepStressUpdate::validParams()
{
  InputParameters params = ADAnisotropicReturnCreepStressUpdateBase::validParams();
  params.addClassDescription(
      "This class uses the stress update material in a generalized radial return anisotropic power "
      "law creep "
      "model.  This class can be used in conjunction with other creep and plasticity materials for "
      "more complex simulations.");

  // Linear strain hardening parameters
  params.addCoupledVar("temperature", "Coupled temperature");
  params.addRequiredParam<Real>("coefficient", "Leading coefficient in power-law equation");
  params.addRequiredParam<Real>("n_exponent", "Exponent on effective stress in power-law equation");
  params.addParam<Real>("m_exponent", 0.0, "Exponent on time in power-law equation");
  params.addRequiredParam<Real>("activation_energy", "Activation energy");
  params.addParam<Real>("gas_constant", 8.3143, "Universal gas constant");
  params.addParam<Real>("start_time", 0.0, "Start time (if not zero)");

  return params;
}

ADHillCreepStressUpdate::ADHillCreepStressUpdate(const InputParameters & parameters)
  : ADAnisotropicReturnCreepStressUpdateBase(parameters),
    _has_temp(isParamValid("temperature")),
    _temperature(_has_temp ? coupledValue("temperature") : _zero),
    _coefficient(getParam<Real>("coefficient")),
    _n_exponent(getParam<Real>("n_exponent")),
    _m_exponent(getParam<Real>("m_exponent")),
    _activation_energy(getParam<Real>("activation_energy")),
    _gas_constant(getParam<Real>("gas_constant")),
    _start_time(getParam<Real>("start_time")),
    _exponential(1.0),
    _exp_time(1.0),
    _hill_constants(getMaterialPropertyByName<std::vector<Real>>(_base_name + "hill_constants")),
    _hill_tensor(_use_transformation
                     ? &getMaterialPropertyByName<DenseMatrix<Real>>(_base_name + "hill_tensor")
                     : nullptr),
    _qsigma(0.0)
{
  if (_start_time < _app.getStartTime() && (std::trunc(_m_exponent) != _m_exponent))
    paramError("start_time",
               "Start time must be equal to or greater than the Executioner start_time if a "
               "non-integer m_exponent is used");
}

void
ADHillCreepStressUpdate::computeStressInitialize(const ADDenseVector & /*stress_dev*/,
                                                 const ADDenseVector & /*stress*/,
                                                 const ADRankFourTensor & elasticity_tensor)
{
  if (_has_temp)
    _exponential = std::exp(-_activation_energy / (_gas_constant * _temperature[_qp]));

  _two_shear_modulus = 2.0 * ElasticityTensorTools::getIsotropicShearModulus(elasticity_tensor);

  _exp_time = std::pow(_t - _start_time, _m_exponent);
}

ADReal
ADHillCreepStressUpdate::initialGuess(const ADDenseVector & /*stress_dev*/)
{
  return 0.0;
}

ADReal
ADHillCreepStressUpdate::computeResidual(const ADDenseVector & /*effective_trial_stress*/,
                                         const ADDenseVector & stress_new,
                                         const ADReal & delta_gamma)
{
  ADReal qsigma_square;
  if (!_use_transformation)
  {
    // Hill constants, some constraints apply
    const Real & F = _hill_constants[_qp][0];
    const Real & G = _hill_constants[_qp][1];
    const Real & H = _hill_constants[_qp][2];
    const Real & L = _hill_constants[_qp][3];
    const Real & M = _hill_constants[_qp][4];
    const Real & N = _hill_constants[_qp][5];

    qsigma_square = F * (stress_new(1) - stress_new(2)) * (stress_new(1) - stress_new(2));
    qsigma_square += G * (stress_new(2) - stress_new(0)) * (stress_new(2) - stress_new(0));
    qsigma_square += H * (stress_new(0) - stress_new(1)) * (stress_new(0) - stress_new(1));
    qsigma_square += 2 * L * stress_new(4) * stress_new(4);
    qsigma_square += 2 * M * stress_new(5) * stress_new(5);
    qsigma_square += 2 * N * stress_new(3) * stress_new(3);
  }
  else
  {
    ADDenseVector Ms(6);
    (*_hill_tensor)[_qp].vector_mult(Ms, stress_new);
    qsigma_square = Ms.dot(stress_new);
  }

  qsigma_square = std::sqrt(qsigma_square);
  qsigma_square -= 1.5 * _two_shear_modulus * delta_gamma;

  const ADReal creep_rate =
      _coefficient * std::pow(qsigma_square, _n_exponent) * _exponential * _exp_time;

  _inelastic_strain_rate[_qp] = MetaPhysicL::raw_value(creep_rate);
  // Return iteration difference between creep strain and inelastic strain multiplier
  return creep_rate * _dt - delta_gamma;
}

Real
ADHillCreepStressUpdate::computeReferenceResidual(
    const ADDenseVector & /*effective_trial_stress*/,
    const ADDenseVector & /*stress_new*/,
    const ADReal & /*residual*/,
    const ADReal & /*scalar_effective_inelastic_strain*/)
{
  return 1.0;
}

ADReal
ADHillCreepStressUpdate::computeDerivative(const ADDenseVector & /*effective_trial_stress*/,
                                           const ADDenseVector & stress_new,
                                           const ADReal & delta_gamma)
{
  ADReal qsigma_square;
  if (!_use_transformation)
  {
    // Hill constants, some constraints apply
    const Real & F = _hill_constants[_qp][0];
    const Real & G = _hill_constants[_qp][1];
    const Real & H = _hill_constants[_qp][2];
    const Real & L = _hill_constants[_qp][3];
    const Real & M = _hill_constants[_qp][4];
    const Real & N = _hill_constants[_qp][5];

    // Equivalent deviatoric stress function.
    qsigma_square = F * (stress_new(1) - stress_new(2)) * (stress_new(1) - stress_new(2));
    qsigma_square += G * (stress_new(2) - stress_new(0)) * (stress_new(2) - stress_new(0));
    qsigma_square += H * (stress_new(0) - stress_new(1)) * (stress_new(0) - stress_new(1));
    qsigma_square += 2 * L * stress_new(4) * stress_new(4);
    qsigma_square += 2 * M * stress_new(5) * stress_new(5);
    qsigma_square += 2 * N * stress_new(3) * stress_new(3);
  }
  else
  {
    ADDenseVector Ms(6);
    (*_hill_tensor)[_qp].vector_mult(Ms, stress_new);
    qsigma_square = Ms.dot(stress_new);
  }

  qsigma_square = std::sqrt(qsigma_square);
  qsigma_square -= 1.5 * _two_shear_modulus * delta_gamma;

  _qsigma = qsigma_square;

  const ADReal creep_rate_derivative = -_coefficient * 1.5 * _two_shear_modulus * _n_exponent *
                                       std::pow(qsigma_square, _n_exponent - 1.0) * _exponential *
                                       _exp_time;
  return (creep_rate_derivative * _dt - 1.0);
}

void
ADHillCreepStressUpdate::computeStrainFinalize(ADRankTwoTensor & inelasticStrainIncrement,
                                               const ADRankTwoTensor & stress,
                                               const ADDenseVector & stress_dev,
                                               const ADReal & delta_gamma)
{
  ADReal qsigma_square;
  if (!_use_transformation)
  {
    // Hill constants, some constraints apply
    const Real & F = _hill_constants[_qp][0];
    const Real & G = _hill_constants[_qp][1];
    const Real & H = _hill_constants[_qp][2];
    const Real & L = _hill_constants[_qp][3];
    const Real & M = _hill_constants[_qp][4];
    const Real & N = _hill_constants[_qp][5];

    // Equivalent deviatoric stress function.
    qsigma_square = F * (stress(1, 1) - stress(2, 2)) * (stress(1, 1) - stress(2, 2));
    qsigma_square += G * (stress(2, 2) - stress(0, 0)) * (stress(2, 2) - stress(0, 0));
    qsigma_square += H * (stress(0, 0) - stress(1, 1)) * (stress(0, 0) - stress(1, 1));
    qsigma_square += 2 * L * stress(1, 2) * stress(1, 2);
    qsigma_square += 2 * M * stress(0, 2) * stress(0, 2);
    qsigma_square += 2 * N * stress(0, 1) * stress(0, 1);
  }
  else
  {
    ADDenseVector Ms(6);
    (*_hill_tensor)[_qp].vector_mult(Ms, stress_dev);
    qsigma_square = Ms.dot(stress_dev);
  }

  if (qsigma_square == 0)
  {
    inelasticStrainIncrement.zero();

    ADAnisotropicReturnCreepStressUpdateBase::computeStrainFinalize(
        inelasticStrainIncrement, stress, stress_dev, delta_gamma);

    _effective_inelastic_strain[_qp] = _effective_inelastic_strain_old[_qp];

    return;
  }

  // Use Hill-type flow rule to compute the time step inelastic increment.
  ADReal prefactor = delta_gamma / std::sqrt(qsigma_square);

  if (!_use_transformation)
  {
    // Hill constants, some constraints apply
    const Real & F = _hill_constants[_qp][0];
    const Real & G = _hill_constants[_qp][1];
    const Real & H = _hill_constants[_qp][2];
    const Real & L = _hill_constants[_qp][3];
    const Real & M = _hill_constants[_qp][4];
    const Real & N = _hill_constants[_qp][5];

    inelasticStrainIncrement(0, 0) =
        prefactor * (H * (stress(0, 0) - stress(1, 1)) - G * (stress(2, 2) - stress(0, 0)));
    inelasticStrainIncrement(1, 1) =
        prefactor * (F * (stress(1, 1) - stress(2, 2)) - H * (stress(0, 0) - stress(1, 1)));
    inelasticStrainIncrement(2, 2) =
        prefactor * (G * (stress(2, 2) - stress(0, 0)) - F * (stress(1, 1) - stress(2, 2)));

    inelasticStrainIncrement(0, 1) = inelasticStrainIncrement(1, 0) =
        prefactor * 2.0 * N * stress(0, 1);
    inelasticStrainIncrement(0, 2) = inelasticStrainIncrement(2, 0) =
        prefactor * 2.0 * M * stress(0, 2);
    inelasticStrainIncrement(1, 2) = inelasticStrainIncrement(2, 1) =
        prefactor * 2.0 * L * stress(1, 2);
  }
  else
  {
    ADDenseVector inelastic_strain_increment(6);
    ADDenseVector Ms(6);
    (*_hill_tensor)[_qp].vector_mult(Ms, stress_dev);

    for (unsigned int i = 0; i < 6; i++)
      inelastic_strain_increment(i) = Ms(i) * prefactor;

    inelasticStrainIncrement(0, 0) = inelastic_strain_increment(0);
    inelasticStrainIncrement(1, 1) = inelastic_strain_increment(1);
    inelasticStrainIncrement(2, 2) = inelastic_strain_increment(2);

    inelasticStrainIncrement(0, 1) = inelasticStrainIncrement(1, 0) = inelastic_strain_increment(3);
    inelasticStrainIncrement(1, 2) = inelasticStrainIncrement(2, 1) = inelastic_strain_increment(4);
    inelasticStrainIncrement(0, 2) = inelasticStrainIncrement(2, 0) = inelastic_strain_increment(5);
  }

  ADAnisotropicReturnCreepStressUpdateBase::computeStrainFinalize(
      inelasticStrainIncrement, stress, stress_dev, delta_gamma);

  _effective_inelastic_strain[_qp] = _effective_inelastic_strain_old[_qp] + delta_gamma;
}

void
ADHillCreepStressUpdate::computeStressFinalize(const ADRankTwoTensor & creepStrainIncrement,
                                               const ADReal & /*delta_gamma*/,
                                               ADRankTwoTensor & stress_new,
                                               const ADDenseVector & /*stress_dev*/,
                                               const ADRankTwoTensor & stress_old,
                                               const ADRankFourTensor & elasticity_tensor)
{
  // Class only valid for isotropic elasticity (for now)
  stress_new -= elasticity_tensor * creepStrainIncrement;

  // Compute the maximum time step allowed due to creep strain numerical integration error
  Real stress_dif = MetaPhysicL::raw_value(stress_new - stress_old).L2norm();

  // Get a representative value of the elasticity tensor
  Real elasticity_value =
      1.0 / 3.0 *
      MetaPhysicL::raw_value((elasticity_tensor(0, 0, 0, 0) + elasticity_tensor(1, 1, 1, 1) +
                              elasticity_tensor(2, 2, 2, 2)));

  if (std::abs(stress_dif) > TOLERANCE * TOLERANCE)
    _max_integration_error_time_step =
        _dt / (stress_dif / elasticity_value / _max_integration_error);
  else
    _max_integration_error_time_step = std::numeric_limits<Real>::max();
}
