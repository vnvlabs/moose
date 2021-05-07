mu=1
rho=1
k=1e-3
cp=1
v_inlet=1
T_inlet=200
advected_interp_method='average'
velocity_interp_method='rc'

[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
    xmin = 0
    xmax = 2
    ymin = 0
    ymax = 10
    nx = 20
    ny = 100
  []
[]

[GlobalParams]
  two_term_boundary_expansion = true
[]

[Variables]
  [u]
    type = PINSFVSuperficialVelocityVariable
    initial_condition = 1e-6
  []
  [v]
    type = PINSFVSuperficialVelocityVariable
    initial_condition = ${v_inlet}
  []
  [pressure]
    type = INSFVPressureVariable
  []
  [temperature]
    type = INSFVEnergyVariable
  []
[]

[AuxVariables]
  [temp_solid]
    family = 'MONOMIAL'
    order = 'CONSTANT'
    fv = true
    initial_condition = 100
  []
  [porosity]
    family = MONOMIAL
    order = CONSTANT
    fv = true
    initial_condition = 0.4
  []
[]

[FVKernels]
  [mass]
    type = PINSFVMassAdvection
    variable = pressure
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    vel = 'velocity'
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    porosity = porosity
  []

  [u_advection]
    type = PINSFVMomentumAdvection
    variable = u
    advected_quantity = 'rhou'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    porosity = porosity
  []
  [u_viscosity]
    type = PINSFVMomentumDiffusion
    variable = u
    mu = ${mu}
    porosity = porosity
  []
  [u_pressure]
    type = PINSFVMomentumPressure
    variable = u
    momentum_component = 'x'
    p = pressure
    porosity = porosity
  []
  [u_gravity]
    type = PINSFVMomentumGravity
    variable = u
    rho = ${rho}
    gravity = '0 -9.81 0'
    momentum_component = 'x'
    porosity = porosity
  []
  [u_boussinesq]
    type = PINSFVMomentumBoussinesq
    variable = u
    temperature = 'temperature'
    rho = ${rho}
    ref_temperature = 150
    gravity = '0 -9.81 0'
    momentum_component = 'x'
    porosity = porosity
  []

  [v_advection]
    type = PINSFVMomentumAdvection
    variable = v
    advected_quantity = 'rhov'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    porosity = porosity
  []
  [v_viscosity]
    type = PINSFVMomentumDiffusion
    variable = v
    mu = ${mu}
    porosity = porosity
  []
  [v_pressure]
    type = PINSFVMomentumPressure
    variable = v
    momentum_component = 'y'
    p = pressure
    porosity = porosity
  []
  [v_gravity]
    type = PINSFVMomentumGravity
    variable = v
    rho = ${rho}
    gravity = '-0 -9.81 0'
    momentum_component = 'y'
    porosity = porosity
  []
  [v_boussinesq]
    type = PINSFVMomentumBoussinesq
    variable = v
    temperature = 'temperature'
    rho = ${rho}
    ref_temperature = 150
    gravity = '0 -9.81 0'
    momentum_component = 'y'
    porosity = porosity
  []

  [energy_advection]
    type = PINSFVEnergyAdvection
    variable = temperature
    vel = 'velocity'
    velocity_interp_method = ${velocity_interp_method}
    advected_interp_method = ${advected_interp_method}
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    porosity = porosity
  []
  [energy_diffusion]
    type = PINSFVEnergyDiffusion
    k = ${k}
    variable = temperature
    porosity = porosity
  []
  [energy_convection]
    type = PINSFVEnergyAmbientConvection
    variable = temperature
    is_solid = false
    temp_fluid = temperature
    temp_solid = temp_solid
    h_solid_fluid = 'h_cv'
  []
[]

[FVBCs]
  [inlet-u]
    type = INSFVInletVelocityBC
    boundary = 'bottom'
    variable = u
    function = 0
  []
  [inlet-v]
    type = INSFVInletVelocityBC
    boundary = 'bottom'
    variable = v
    function = ${v_inlet}
  []
  [inlet-T]
    type = FVNeumannBC
    variable = temperature
    value = ${fparse v_inlet * rho * cp * T_inlet}
    boundary = 'bottom'
  []

  [no-slip-u]
    type = INSFVNoSlipWallBC
    boundary = 'right'
    variable = u
    function = 0
  []
  [no-slip-v]
    type = INSFVNoSlipWallBC
    boundary = 'right'
    variable = v
    function = 0
  []

  [symmetry-u]
    type = PINSFVSymmetryVelocityBC
    boundary = 'left'
    variable = u
    u = u
    v = v
    mu = ${mu}
    momentum_component = 'x'
    porosity = porosity
  []
  [symmetry-v]
    type = PINSFVSymmetryVelocityBC
    boundary = 'left'
    variable = v
    u = u
    v = v
    mu = ${mu}
    momentum_component = 'y'
    porosity = porosity
  []
  [symmetry-p]
    type = INSFVSymmetryPressureBC
    boundary = 'left'
    variable = pressure
  []

  [outlet-p]
    type = INSFVOutletPressureBC
    boundary = 'top'
    variable = pressure
    function = 0
  []
[]

[Materials]
  [constants]
    type = ADGenericConstantMaterial
    prop_names = 'cp h_cv alpha'
    prop_values = '${cp} 1e-3 8e-4'
  []

  [ins_fv]
    type = INSFVMaterial
    u = 'u'
    v = 'v'
    pressure = 'pressure'
    rho = ${rho}
    temperature = 'temperature'
  []
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_pc_type -sub_pc_factor_shift_type'
  petsc_options_value = 'asm      100                lu           NONZERO'
  line_search = 'none'
  nl_rel_tol = 1e-12
[]

# Some basic Postprocessors to examine the solution
[Postprocessors]
  [inlet-p]
    type = SideAverageValue
    variable = pressure
    boundary = 'top'
  []
  [outlet-v]
    type = SideAverageValue
    variable = v
    boundary = 'top'
  []
  [outlet-temp]
    type = SideAverageValue
    variable = temperature
    boundary = 'top'
  []
[]

[Outputs]
  exodus = true
  csv = false
[]
