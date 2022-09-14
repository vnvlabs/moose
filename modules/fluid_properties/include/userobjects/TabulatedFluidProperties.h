//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "SinglePhaseFluidProperties.h"
#include "DelimitedFileReader.h"

#include "libmesh/utility.h"

class SinglePhaseFluidProperties;
class BidimensionalInterpolation;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"

/**
 * Class for fluid properties read from a file.
 *
 * Property values are read from a CSV file containing property data.
 * Monotonically increasing values of pressure and temperature must be included in
 * the data file, specifying the phase space where tabulated fluid properties will
 * be defined. An error is thrown if either temperature or pressure data is not
 * included or not monotonic, and an error is also thrown if this UserObject is
 * requested to provide a fluid property outside this phase space.
 *
 * This class is intended to be used when complicated formulations for fluid properties
 * (for example, density or enthalpy) are required, which can be computationally expensive.
 * This is particularly the case where the fluid equation of state is based on a
 * Helmholtz free energy that is a function of density and temperature, like that
 * used in CO2FluidProperties. In this case, density must be solved iteratively using
 * pressure and temperature, which increases the computational burden.
 *
 * Using interpolation to calculate these fluid properties can significantly reduce
 * the computational time for these cases.
 *
 * The expected file format for the tabulated fluid properties is now described.
 * The first line must be the header containing the required column
 * names "pressure" and "temperature", and the names of the fluid properties to be
 * read. Available fluid property names are:
 * "density", "enthalpy", "internal_energy", "viscosity", "k" (thermal conductivity),
 * "cp" (isobaric specific heat capacity), "cv" (isochoric specific heat capacity),
 * and "entropy".
 * Note: the order is not important, although having pressure and temperature first
 * makes the data easier for a human to read).
 *
 * The data in the pressure and temperature columns must be monotonically increasing. This file
 * format does require duplication of the pressure and temperature data - each pressure value
 * must be included num_T times, while each temperature value is repeated num_p times, where
 * num_T and num_p are the number of temperature and pressure points, respectively. This class
 * will check that the required number of data points have been entered (num_T * num_p).
 *
 * An example of a valid fluid properties file is provided below:
 *
 * pressure, temperature,   density, enthalpy, internal_energy
 *   200000,         275,   3.90056,   -21487,        -72761.7
 *   200000,         277,   3.86573, -19495.4,        -71232.0
 *   200000,         280,   3.83155, -17499.1,        -69697.3
 *   300000,         275,   6.07273, -22728.3,        -73626.5
 *   300000,         277,   6.01721, -20711.5,        -72079.3
 *   300000,         280,   5.96277, -18691.0,        -70527.7
 *
 * and so on.
 *
 * If no tabulated fluid property data file exists, then data for the fluid supplied
 * by the required FluidProperties UserObject will be generated using the pressure
 * and temperature ranges specified in the input file at the beginning of the simulation.
 * The properties to be tabulated are provided in the "interpolated_properties" input
 * parameter (the properties that can be tabulated are listed above).
 *
 * This tabulated data will be written to file in the correct format,
 * enabling suitable data files to be created for future use. There is an upfront
 * computational expense required for this initial data generation, depending on the
 * required number of pressure and temperature points. However, provided that the
 * number of data points required to generate the tabulated data is smaller than the
 * number of times the property members in the FluidProperties UserObject are used,
 * the initial time to generate the data and the subsequent interpolation time can be much
 * less than using the original FluidProperties UserObject.
 *
 * Properties specified in the data file or listed in the input file (and their derivatives
 * wrt pressure and temperature) will be calculated using bi-dimensional interpolation, while all
 * remaining fluid properties are calculated using the supplied FluidProperties UserObject.
 */
class TabulatedFluidProperties : public SinglePhaseFluidProperties
{
public:
  static InputParameters validParams();

  TabulatedFluidProperties(const InputParameters & parameters);

  virtual void initialSetup() override;
  virtual void constructInterpolation() = 0;

  virtual std::string fluidName() const override;

  virtual Real molarMass() const override;

  virtual Real rho_from_p_T(Real pressure, Real temperature) const override;

  virtual void rho_from_p_T(
      Real pressure, Real temperature, Real & rho, Real & drho_dp, Real & drho_dT) const override;
  virtual void rho_from_p_T(const ADReal & pressure,
                            const ADReal & temperature,
                            ADReal & rho,
                            ADReal & drho_dp,
                            ADReal & drho_dT) const override;

  virtual Real v_from_p_T(Real pressure, Real temperature) const override;

  virtual void
  v_from_p_T(Real pressure, Real temperature, Real & v, Real & dv_dp, Real & dv_dT) const override;

  virtual Real e_from_p_T(Real pressure, Real temperature) const override;

  virtual void
  e_from_p_T(Real pressure, Real temperature, Real & e, Real & de_dp, Real & de_dT) const override;

  virtual Real e_from_p_rho(Real pressure, Real rho) const override;

  virtual void
  e_from_p_rho(Real pressure, Real rho, Real & e, Real & de_dp, Real & de_drho) const override;

  virtual Real T_from_p_rho(Real pressure, Real rho) const;

  virtual void T_from_p_rho(Real pressure, Real rho, Real & T, Real & dT_dp, Real & dT_drho) const;

  virtual Real h_from_p_T(Real p, Real T) const override;

  virtual void
  h_from_p_T(Real pressure, Real temperature, Real & h, Real & dh_dp, Real & dh_dT) const override;

  virtual Real mu_from_p_T(Real pressure, Real temperature) const override;

  virtual void mu_from_p_T(
      Real pressure, Real temperature, Real & mu, Real & dmu_dp, Real & dmu_dT) const override;

  virtual Real cp_from_p_T(Real pressure, Real temperature) const override;

  virtual void cp_from_p_T(
      Real pressure, Real temperature, Real & cp, Real & dcp_dp, Real & dcp_dT) const override;

  using SinglePhaseFluidProperties::cp_from_p_T;

  virtual Real cv_from_p_T(Real pressure, Real temperature) const override;
  virtual void cv_from_p_T(
      Real pressure, Real temperature, Real & cv, Real & dcv_dp, Real & dcv_dT) const override;

  virtual Real c_from_p_T(Real pressure, Real temperature) const override;
  virtual void
  c_from_p_T(Real pressure, Real temperature, Real & c, Real & dc_dp, Real & dc_dT) const override;

  virtual Real k_from_p_T(Real pressure, Real temperature) const override;

  virtual void
  k_from_p_T(Real pressure, Real temperature, Real & k, Real & dk_dp, Real & dk_dT) const override;

  virtual Real s_from_p_T(Real pressure, Real temperature) const override;

  virtual void s_from_p_T(Real p, Real T, Real & s, Real & ds_dp, Real & ds_dT) const override;

  virtual std::vector<Real> henryCoefficients() const override;

  virtual Real vaporPressure(Real temperature) const override;

  virtual void vaporPressure(Real temperature, Real & psat, Real & dpsat_dT) const override;

  /**
   * Derivatives like dc_dv & dc_de are computed using the chain rule
   * dy/dx(p,T) = dy/dp * dp/dx + dy/dT * dT/dx
   * where y = c, cp, cv... & x = v, e
   */
  virtual Real p_from_v_e(Real v, Real e) const override;
  virtual void p_from_v_e(Real v, Real e, Real & p, Real & dp_dv, Real & dp_de) const override;
  virtual Real T_from_v_e(Real v, Real e) const override;
  virtual void T_from_v_e(Real v, Real e, Real & T, Real & dT_dv, Real & dT_de) const override;
  virtual Real c_from_v_e(Real v, Real e) const override;
  virtual void c_from_v_e(Real v, Real e, Real & c, Real & dc_dv, Real & dc_de) const override;
  virtual Real cp_from_v_e(Real v, Real e) const override;
  virtual void cp_from_v_e(Real v, Real e, Real & cp, Real & dcp_dv, Real & dcp_de) const override;
  virtual Real cv_from_v_e(Real v, Real e) const override;
  virtual void cv_from_v_e(Real v, Real e, Real & cv, Real & dcv_dv, Real & dcv_de) const override;
  virtual Real mu_from_v_e(Real v, Real e) const override;
  virtual void mu_from_v_e(Real v, Real e, Real & mu, Real & dmu_dv, Real & dmu_de) const override;
  virtual Real k_from_v_e(Real v, Real e) const override;
  virtual void k_from_v_e(Real v, Real e, Real & k, Real & dk_dv, Real & dk_de) const override;
  virtual Real g_from_v_e(Real v, Real e) const override;
  virtual Real e_from_v_h(Real v, Real h) const override;
  virtual void e_from_v_h(Real v, Real h, Real & e, Real & de_dv, Real & de_dh) const override;
  virtual Real T_from_h_s(Real h, Real s) const;
  virtual Real T_from_h_p(Real h, Real pressure) const override;
  virtual Real s_from_h_p(Real h, Real pressure) const override;

  // AD versions of properties
  virtual DualReal p_from_v_e(const DualReal & v, const DualReal & e) const override;
  virtual DualReal T_from_v_e(const DualReal & v, const DualReal & e) const override;
  virtual DualReal c_from_v_e(const DualReal & v, const DualReal & e) const override;

protected:
  /**
   * Writes tabulated data to a file.
   * @param file_name name of the file to be written
   */
  void writeTabulatedData(std::string file_name);

  /**
   * Checks that the inputs are within the range of the tabulated data, and throws
   * an error if they are not.
   * @param pressure input pressure (Pa)
   * @param temperature input temperature (K)
   */
  template <typename T>
  void checkInputVariables(T & pressure, T & temperature) const;

  /**
   * Checks initial guess for Newton Method
   */
  virtual void checkInitialGuess() const;

  /**
   * Generates a table of fluid properties by looping over pressure and temperature
   * and calculating properties using the FluidProperties UserObject _fp.
   */
  virtual void generateTabulatedData();

  Real inverseDistance(const std::vector<Real> & value, const std::vector<Real> & distance) const;

  // File name of tabulated data file
  FileName _file_name;
  // Pressure vector
  std::vector<Real> _pressure;
  // Temperature vector
  std::vector<Real> _temperature;
  // Tabulated fluid properties
  std::vector<std::vector<Real>> _properties;

  // Vector of bi-dimensional interpolation of fluid properties
  std::vector<std::unique_ptr<BidimensionalInterpolation>> _property_ipol;

  // Minimum temperature in tabulated data
  Real _temperature_min;
  // Maximum temperature in tabulated data
  Real _temperature_max;
  // Minimum pressure in tabulated data
  Real _pressure_min;
  // Maximum pressure in tabulated data
  Real _pressure_max;
  // Number of temperature points in the tabulated data
  unsigned int _num_T;
  // Number of pressure points in the tabulated data
  unsigned int _num_p;
  // Whether to save a generated fluid properties file to disk
  const bool _save_file;

  // SinglePhaseFluidPropertiesPT UserObject
  const SinglePhaseFluidProperties * const _fp;

  // List of required column names to be read
  const std::vector<std::string> _required_columns{"pressure", "temperature"};
  // List of possible property column names to be read
  const std::vector<std::string> _property_columns{
      "density", "enthalpy", "internal_energy", "viscosity", "k", "c", "cv", "cp", "entropy"};
  // Properties to be interpolated entered in the input file
  MultiMooseEnum _interpolated_properties_enum;
  // List of properties to be interpolated
  std::vector<std::string> _interpolated_properties;
  // Set of flags to note whether a property is to be interpolated
  bool _interpolate_density;
  bool _interpolate_enthalpy;
  bool _interpolate_internal_energy;
  bool _interpolate_viscosity;
  bool _interpolate_k;
  bool _interpolate_c;
  bool _interpolate_cp;
  bool _interpolate_cv;
  bool _interpolate_entropy;

  // Index of each property
  unsigned int _density_idx;
  unsigned int _enthalpy_idx;
  unsigned int _internal_energy_idx;
  unsigned int _viscosity_idx;
  unsigned int _k_idx;
  unsigned int _c_idx;
  unsigned int _cp_idx;
  unsigned int _cv_idx;
  unsigned int _entropy_idx;

  // The MOOSE delimited file reader.
  MooseUtils::DelimitedFileReader _csv_reader;

  // if the lookup table p(v, e) and T(v, e) should be constructed
  bool _construct_pT_from_ve;
  // if the lookup table p(v, h) and T(v, h) should be constructed
  bool _construct_pT_from_vh;
  // keeps track of whether initialSetup has been preformed
  bool _initial_setup_done;
  // Number of specific volume points in the tabulated data
  unsigned int _num_v;
  // Number of internal energy points in tabulated data
  unsigned int _num_e;
  // to error or not on out of bounds check
  bool _error_on_out_of_bounds;

  // Bi-dimensional interpolation of temperature from (v,e)
  std::unique_ptr<BidimensionalInterpolation> _T_from_v_e_ipol;

  // Bi-dimensional interpolation of pressure from (v,e)
  std::unique_ptr<BidimensionalInterpolation> _p_from_v_e_ipol;

  // Bidimensional interpolation of temperature from (v,h)
  std::unique_ptr<BidimensionalInterpolation> _T_from_v_h_ipol;

  // Bidimensional interpolation of pressure from (v,h)
  std::unique_ptr<BidimensionalInterpolation> _p_from_v_h_ipol;

  // Minimum internal energy in tabulated data
  Real _e_min;
  // Maximum internal energy in tabulated data
  Real _e_max;
  // Minimum specific volume in tabulated data
  Real _v_min;
  // Maximum specific volume in tabulated data
  Real _v_max;
  // Minimum specific enthalpy in tabulated data
  Real _h_min;
  // Maximum specific enthalpy in tabulated data
  Real _h_max;

  // specific volume vector
  std::vector<Real> _specific_volume;
  // internal energy vector
  std::vector<Real> _internal_energy;
  // enthalpy vector
  std::vector<Real> _enthalpy;
};

#pragma GCC diagnostic pop
