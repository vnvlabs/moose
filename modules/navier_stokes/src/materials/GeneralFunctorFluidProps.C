//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "GeneralFunctorFluidProps.h"
#include "NS.h" // Variable Term Names
#include "DimensionlessFlowNumbers.h"
#include "NavierStokesMethods.h"
#include "SinglePhaseFluidProperties.h"

registerMooseObject("NavierStokesApp", GeneralFunctorFluidProps);

InputParameters
GeneralFunctorFluidProps::validParams()
{
  auto params = FunctorMaterial::validParams();
  params.addRequiredParam<UserObjectName>(NS::fluid, "Fluid properties functor userobject");
  params.addClassDescription("Creates functor fluid properties using a (P, T) formulation");

  params.addRequiredParam<MooseFunctorName>(NS::pressure, "Pressure");
  params.addRequiredParam<MooseFunctorName>(NS::T_fluid, "Fluid temperature");
  params.addRequiredParam<MooseFunctorName>(NS::speed, "Velocity norm");
  params.addParam<MooseFunctorName>(NS::density, "Density");
  params.addParam<bool>(
      "force_define_density",
      false,
      "Whether to force the definition of a density functor from the fluid properties");

  params.addParam<FunctionName>(
      "mu_rampdown", 1, "A function describing a ramp down of viscosity over time");
  params.addRequiredParam<MooseFunctorName>(NS::porosity, "porosity");
  params.addRequiredRangeCheckedParam<Real>(
      "characteristic_length",
      "characteristic_length > 0.0",
      "characteristic length for Reynolds number calculation");
  return params;
}

GeneralFunctorFluidProps::GeneralFunctorFluidProps(const InputParameters & parameters)
  : FunctorMaterial(parameters),
    _fluid(UserObjectInterface::getUserObject<SinglePhaseFluidProperties>(NS::fluid)),
    _eps(getFunctor<ADReal>(NS::porosity)),
    _d(getParam<Real>("characteristic_length")),

    _pressure(getFunctor<ADReal>(NS::pressure)),
    _T_fluid(getFunctor<ADReal>(NS::T_fluid)),
    _speed(getFunctor<ADReal>(NS::speed)),
    _force_define_density(getParam<bool>("force_define_density")),
    _rho(getFunctor<ADReal>(NS::density)),
    _mu_rampdown(getFunction("mu_rampdown"))
{
  //
  // Set material properties functors
  //

  if (!isParamValid(NS::density) || _force_define_density)
    addFunctorProperty<ADReal>(NS::density,
                               [this](const auto & r, const auto & t) -> ADReal
                               { return _fluid.rho_from_p_T(_pressure(r, t), _T_fluid(r, t)); });

  addFunctorProperty<ADReal>(NS::cv,
                             [this](const auto & r, const auto & t) -> ADReal
                             { return _fluid.cv_from_p_T(_pressure(r, t), _T_fluid(r, t)); });

  const auto & cp =
      addFunctorProperty<ADReal>(NS::cp,
                                 [this](const auto & r, const auto & t) -> ADReal
                                 { return _fluid.cp_from_p_T(_pressure(r, t), _T_fluid(r, t)); });

  const auto & mu = addFunctorProperty<ADReal>(
      NS::mu,
      [this](const auto & r, const auto & t) -> ADReal
      { return _mu_rampdown(r, t) * _fluid.mu_from_p_T(_pressure(r, t), _T_fluid(r, t)); });

  const auto & k =
      addFunctorProperty<ADReal>(NS::k,
                                 [this](const auto & r, const auto & t) -> ADReal
                                 { return _fluid.k_from_p_T(_pressure(r, t), _T_fluid(r, t)); });

  //
  // Time derivatives of fluid properties
  //

  addFunctorProperty<ADReal>(NS::time_deriv(NS::density),
                             [this](const auto & r, const auto & t) -> ADReal
                             {
                               ADReal rho, drho_dp, drho_dT;
                               _fluid.rho_from_p_T(
                                   _pressure(r, t), _T_fluid(r, t), rho, drho_dp, drho_dT);
                               return drho_dp * _pressure.dot(r, t) + drho_dT * _T_fluid.dot(r, t);
                             });

  addFunctorProperty<ADReal>(NS::time_deriv(NS::cp),
                             [this](const auto & r, const auto & t) -> ADReal
                             {
                               Real dcp_dp, dcp_dT, dummy;
                               auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
                               auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));
                               _fluid.cp_from_p_T(raw_pressure, raw_T_fluid, dummy, dcp_dp, dcp_dT);

                               return dcp_dp * _pressure.dot(r, t) + dcp_dT * _T_fluid.dot(r, t);
                             });

  //
  // Temperature and pressure derivatives, to help with computing time derivatives
  //

  const auto & drho_dp = addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::density, NS::pressure),
      [this](const auto & r, const auto & t) -> Real
      {
        Real drho_dp, drho_dT, dummy;
        auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
        auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

        _fluid.rho_from_p_T(raw_pressure, raw_T_fluid, dummy, drho_dp, drho_dT);
        return drho_dp;
      });

  const auto & drho_dT = addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::density, NS::T_fluid),
      [this](const auto & r, const auto & t) -> Real
      {
        Real drho_dp, drho_dT, dummy;
        auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
        auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

        _fluid.rho_from_p_T(raw_pressure, raw_T_fluid, dummy, drho_dp, drho_dT);
        return drho_dT;
      });

  const auto & dcp_dp = addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::cp, NS::pressure),
      [this](const auto & r, const auto & t) -> Real
      {
        Real dcp_dp, dcp_dT, dummy;
        auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
        auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

        _fluid.cp_from_p_T(raw_pressure, raw_T_fluid, dummy, dcp_dp, dcp_dT);
        return dcp_dp;
      });

  const auto & dcp_dT = addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::cp, NS::T_fluid),
      [this](const auto & r, const auto & t) -> Real
      {
        Real dcp_dp, dcp_dT, dummy;
        auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
        auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

        _fluid.cp_from_p_T(raw_pressure, raw_T_fluid, dummy, dcp_dp, dcp_dT);
        return dcp_dT;
      });

  const auto & dmu_dp = addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::mu, NS::pressure),
      [this](const auto & r, const auto & t) -> Real
      {
        Real dmu_dp, dmu_dT, dummy;
        auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
        auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

        _fluid.mu_from_p_T(raw_pressure, raw_T_fluid, dummy, dmu_dp, dmu_dT);
        return _mu_rampdown(r, t) * dmu_dp;
      });

  const auto & dmu_dT = addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::mu, NS::T_fluid),
      [this](const auto & r, const auto & t) -> Real
      {
        Real dmu_dp, dmu_dT, dummy;
        auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
        auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

        _fluid.mu_from_p_T(raw_pressure, raw_T_fluid, dummy, dmu_dp, dmu_dT);
        return _mu_rampdown(r, t) * dmu_dT;
      });

  const auto & dk_dp =
      addFunctorProperty<Real>(derivativePropertyNameFirst(NS::k, NS::pressure),
                               [this](const auto & r, const auto & t) -> Real
                               {
                                 Real dk_dp, dk_dT, dummy;
                                 auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
                                 auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

                                 _fluid.k_from_p_T(raw_pressure, raw_T_fluid, dummy, dk_dp, dk_dT);
                                 return dk_dp;
                               });

  const auto & dk_dT =
      addFunctorProperty<Real>(derivativePropertyNameFirst(NS::k, NS::T_fluid),
                               [this](const auto & r, const auto & t) -> Real
                               {
                                 Real dk_dp, dk_dT, dummy;
                                 auto raw_pressure = MetaPhysicL::raw_value(_pressure(r, t));
                                 auto raw_T_fluid = MetaPhysicL::raw_value(_T_fluid(r, t));

                                 _fluid.k_from_p_T(raw_pressure, raw_T_fluid, dummy, dk_dp, dk_dT);
                                 return dk_dT;
                               });

  //
  // Fluid adimensional quantities, used in numerous correlations
  //

  addFunctorProperty<ADReal>(NS::Prandtl,
                             [&cp, &mu, &k](const auto & r, const auto & t) -> ADReal
                             {
                               static constexpr Real small_number = 1e-8;

                               return fp::prandtl(
                                   cp(r, t), mu(r, t), std::max(k(r, t), small_number));
                             });

  addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::Prandtl, NS::pressure),
      [&mu, &cp, &k, &dmu_dp, &dcp_dp, &dk_dp](const auto & r, const auto & t) -> Real
      {
        return prandtlPropertyDerivative(MetaPhysicL::raw_value(mu(r, t)),
                                         MetaPhysicL::raw_value(cp(r, t)),
                                         MetaPhysicL::raw_value(k(r, t)),
                                         dmu_dp(r, t),
                                         dcp_dp(r, t),
                                         dk_dp(r, t));
      });

  addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::Prandtl, NS::T_fluid),
      [&mu, &cp, &k, &dmu_dT, &dcp_dT, &dk_dT](const auto & r, const auto & t) -> Real
      {
        return prandtlPropertyDerivative(MetaPhysicL::raw_value(mu(r, t)),
                                         MetaPhysicL::raw_value(cp(r, t)),
                                         MetaPhysicL::raw_value(k(r, t)),
                                         dmu_dT(r, t),
                                         dcp_dT(r, t),
                                         dk_dT(r, t));
      });

  //
  // (pore / particle) Reynolds number based on superficial velocity and
  // characteristic length. Only call Reynolds() one time to compute all three so that
  // we don't redundantly check that viscosity is not too close to zero.
  //

  const auto & Re =
      addFunctorProperty<ADReal>(NS::Reynolds,
                                 [this, &mu](const auto & r, const auto & t) -> ADReal
                                 {
                                   static constexpr Real small_number = 1e-8;
                                   return std::max(fp::reynolds(_rho(r, t),
                                                                _eps(r, t) * _speed(r, t),
                                                                _d,
                                                                std::max(mu(r, t), small_number)),
                                                   small_number);
                                 });

  addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::Reynolds, NS::pressure),
      [this, &Re, &mu, &drho_dp, &dmu_dp](const auto & r, const auto & t) -> Real
      {
        return reynoldsPropertyDerivative(MetaPhysicL::raw_value(Re(r, t)),
                                          MetaPhysicL::raw_value(_rho(r, t)),
                                          MetaPhysicL::raw_value(mu(r, t)),
                                          drho_dp(r, t),
                                          dmu_dp(r, t));
      });

  addFunctorProperty<Real>(
      derivativePropertyNameFirst(NS::Reynolds, NS::T_fluid),
      [this, &Re, &mu, &drho_dT, &dmu_dT](const auto & r, const auto & t) -> Real
      {
        return reynoldsPropertyDerivative(MetaPhysicL::raw_value(Re(r, t)),
                                          MetaPhysicL::raw_value(_rho(r, t)),
                                          MetaPhysicL::raw_value(mu(r, t)),
                                          drho_dT(r, t),
                                          dmu_dT(r, t));
      });

  // (hydraulic) Reynolds number
  addFunctorProperty<ADReal>(NS::Reynolds_hydraulic,
                             [this, &Re](const auto & r, const auto & t) -> ADReal
                             {
                               static constexpr Real small_number = 1e-8;
                               return Re(r, t) / std::max(1 - _eps(r, t), small_number);
                             });

  // (interstitial) Reynolds number
  addFunctorProperty<ADReal>(NS::Reynolds_interstitial,
                             [this, &Re](const auto & r, const auto & t) -> ADReal
                             {
                               return Re(r, t) / _eps(r, t);
                               ;
                             });
}
