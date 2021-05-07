mu=1.1
rho=1
advected_interp_method='average'
velocity_interp_method='average'

[GlobalParams]
  two_term_boundary_expansion = true
[]

[Mesh]
  inactive = 'mesh internal_boundary_bot internal_boundary_top'
  [mesh]
    type = CartesianMeshGenerator
    dim = 2
    dx = '1'
    dy = '1 1 1'
    ix = '5'
    iy = '5 5 5'
    subdomain_id = '1
                    2
                    3'
  []
  [internal_boundary_bot]
    type = SideSetsBetweenSubdomainsGenerator
    input = mesh
    new_boundary = 'internal_bot'
    primary_block = 1
    paired_block = 2
  []
  [internal_boundary_top]
    type = SideSetsBetweenSubdomainsGenerator
    input = internal_boundary_bot
    new_boundary = 'internal_top'
    primary_block = 2
    paired_block = 3
  []
  [diverging_mesh]
    type = FileMeshGenerator
    file = 'expansion_quad.e'
  []
[]

[Problem]
  fv_bcs_integrity_check = true
[]

[Variables]
  [u]
    type = INSFVVelocityVariable
    initial_condition = 0
  []
  [v]
    type = INSFVVelocityVariable
    initial_condition = 1
  []
  [pressure]
    type = INSFVPressureVariable
  []
  [temperature]
    type = INSFVEnergyVariable
  []
[]

[AuxVariables]
  [advected_density]
    order = CONSTANT
    family = MONOMIAL
    fv = true
    initial_condition = ${rho}
  []
[]

[FVKernels]
  [mass]
    type = INSFVMassAdvection
    variable = pressure
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    vel = 'velocity'
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
  []

  [u_advection]
    type = INSFVMomentumAdvection
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
  []
  [u_viscosity]
    type = FVDiffusion
    variable = u
    coeff = ${mu}
    force_boundary_execution = true
  []
  [u_pressure]
    type = INSFVMomentumPressure
    variable = u
    momentum_component = 'x'
    p = pressure
  []

  [v_advection]
    type = INSFVMomentumAdvection
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
  []
  [v_viscosity]
    type = FVDiffusion
    variable = v
    coeff = ${mu}
    force_boundary_execution = true
  []
  [v_pressure]
    type = INSFVMomentumPressure
    variable = v
    momentum_component = 'y'
    p = pressure
  []

  [temp_advection]
    type = INSFVEnergyAdvection
    vel = 'velocity'
    variable = temperature
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
  []
  [temp_source]
    type = FVBodyForce
    variable = temperature
    function = 10
    block = 1
  []
[]

[FVBCs]
  inactive = 'noslip-u noslip-v'
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
    function = 1
  []
  [noslip-u]
    type = INSFVNoSlipWallBC
    boundary = 'right'
    variable = u
    function = 0
  []
  [noslip-v]
    type = INSFVNoSlipWallBC
    boundary = 'right'
    variable = v
    function = 0
  []
  [free-slip-u]
    type = INSFVNaturalFreeSlipBC
    boundary = 'right'
    variable = u
  []
  [free-slip-v]
    type = INSFVNaturalFreeSlipBC
    boundary = 'right'
    variable = v
  []
  [axis-u]
    type = INSFVSymmetryVelocityBC
    boundary = 'left'
    variable = u
    u = u
    v = v
    mu = ${mu}
    momentum_component = x
  []
  [axis-v]
    type = INSFVSymmetryVelocityBC
    boundary = 'left'
    variable = v
    u = u
    v = v
    mu = ${mu}
    momentum_component = y
  []
  [axis-p]
    type = INSFVSymmetryPressureBC
    boundary = 'left'
    variable = pressure
  []
  [outlet_p]
    type = INSFVOutletPressureBC
    boundary = 'top'
    variable = pressure
    function = 0
  []
  [inlet_temp]
    type = FVNeumannBC
    boundary = 'bottom'
    variable = temperature
    value = 300
  []
[]

[Materials]
  [ins_fv]
    type = INSFVMaterial
    u = 'u'
    v = 'v'
    pressure = 'pressure'
    temperature = 'temperature'
    rho = ${rho}
  []
  [advected_material_property]
    type = ADGenericConstantMaterial
    prop_names = 'advected_rho cp'
    prop_values ='${rho} 1'
  []
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_pc_type -sub_pc_factor_shift_type'
  petsc_options_value = 'asm      200                lu           NONZERO'
  line_search = 'none'
  nl_rel_tol = 1e-12
[]

[Postprocessors]
  [inlet_mass_variable]
    type = VolumetricFlowRate
    boundary = bottom
    vel_x = u
    vel_y = v
    advected_variable = advected_density
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [inlet_mass_constant]
    type = VolumetricFlowRate
    boundary = bottom
    vel_x = u
    vel_y = v
    advected_variable = ${rho}
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [inlet_mass_matprop]
    type = VolumetricFlowRate
    boundary = bottom
    vel_x = u
    vel_y = v
    advected_mat_prop = 'advected_rho'
    fv = true
  []
  [mid1_mass]
    type = InternalVolumetricFlowRate
    boundary = internal_bot
    vel_x = u
    vel_y = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [mid2_mass]
    type = InternalVolumetricFlowRate
    boundary = internal_top
    vel_x = u
    vel_y = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [outlet_mass]
    type = VolumetricFlowRate
    boundary = top
    vel_x = u
    vel_y = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []

  [inlet_momentum_x]
    type = VolumetricFlowRate
    boundary = bottom
    vel_x = u
    vel_y = v
    advected_variable = u
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [mid1_momentum_x]
    type = InternalVolumetricFlowRate
    boundary = internal_bot
    vel_x = u
    vel_y = v
    advected_variable = u
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [mid2_momentum_x]
    type = InternalVolumetricFlowRate
    boundary = internal_top
    vel_x = u
    vel_y = v
    advected_variable = u
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [outlet_momentum_x]
    type = VolumetricFlowRate
    boundary = top
    vel_x = u
    vel_y = v
    advected_variable = u
    fv = true
    advected_interp_method = ${advected_interp_method}
  []

  [inlet_momentum_y]
    type = VolumetricFlowRate
    boundary = bottom
    vel_x = u
    vel_y = v
    advected_variable = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [mid1_momentum_y]
    type = InternalVolumetricFlowRate
    boundary = internal_bot
    vel_x = u
    vel_y = v
    advected_variable = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [mid2_momentum_y]
    type = InternalVolumetricFlowRate
    boundary = internal_top
    vel_x = u
    vel_y = v
    advected_variable = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [outlet_momentum_y]
    type = VolumetricFlowRate
    boundary = top
    vel_x = u
    vel_y = v
    advected_variable = v
    fv = true
    advected_interp_method = ${advected_interp_method}
  []

  [inlet_advected_energy]
    type = VolumetricFlowRate
    boundary = bottom
    vel_x = u
    vel_y = v
    advected_mat_prop = 'rho_cp_temp'
    fv = true
  []
  [mid1_advected_energy]
    type = InternalVolumetricFlowRate
    boundary = internal_bot
    vel_x = u
    vel_y = v
    advected_mat_prop = 'rho_cp_temp'
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [mid2_advected_energy]
    type = InternalVolumetricFlowRate
    boundary = internal_top
    vel_x = u
    vel_y = v
    advected_mat_prop = 'rho_cp_temp'
    fv = true
    advected_interp_method = ${advected_interp_method}
  []
  [outlet_advected_energy]
    type = VolumetricFlowRate
    boundary = top
    vel_x = u
    vel_y = v
    advected_mat_prop = 'rho_cp_temp'
    fv = true
  []
[]

[Outputs]
  exodus = false
  csv = true
  inactive = 'console_mass console_momentum_x console_momentum_y console_energy'
  [console_mass]
    type = Console
    start_step = 1
    show = 'inlet_mass_variable inlet_mass_constant inlet_mass_matprop mid1_mass mid2_mass outlet_mass'
  []
  [console_momentum_x]
    type = Console
    start_step = 1
    show = 'inlet_momentum_x mid1_momentum_x mid2_momentum_x outlet_momentum_x'
  []
  [console_momentum_y]
    type = Console
    start_step = 1
    show = 'inlet_momentum_y mid1_momentum_y mid2_momentum_y outlet_momentum_y'
  []
  [console_energy]
    type = Console
    start_step = 1
    show = 'inlet_advected_energy mid1_advected_energy mid2_advected_energy outlet_advected_energy'
  []
[]
