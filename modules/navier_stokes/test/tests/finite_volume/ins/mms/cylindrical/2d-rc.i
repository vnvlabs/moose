mu=1.1
rho=1.1

[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
    xmin = 1
    xmax = 3
    ymin = -1
    ymax = 1
    nx = 2
    ny = 2
  []
[]

[Problem]
  coord_type = 'RZ'
[]

[Variables]
  [u]
    type = INSFVVelocityVariable
    initial_condition = 1
  []
  [v]
    type = INSFVVelocityVariable
    initial_condition = 1
  []
  [pressure]
    type = INSFVPressureVariable
  []
  [lambda]
    family = SCALAR
    order = FIRST
  []
[]

[FVKernels]
  [mass]
    type = INSFVMassAdvection
    variable = pressure
    advected_interp_method = 'average'
    velocity_interp_method = 'rc'
    vel = 'velocity'
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    no_slip_wall_boundaries = 'left right top bottom'
  []
  [mass_forcing]
    type = FVBodyForce
    variable = pressure
    function = forcing_p
  []
  [mean_zero_pressure]
    type = FVScalarLagrangeMultiplier
    variable = pressure
    lambda = lambda
  []

  [u_advection]
    type = INSFVMomentumAdvection
    variable = u
    advected_quantity = 'rhou'
    vel = 'velocity'
    advected_interp_method = 'average'
    velocity_interp_method = 'rc'
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    no_slip_wall_boundaries = 'left right top bottom'
  []
  [u_viscosity]
    type = FVDiffusion
    variable = u
    coeff = ${mu}
  []
  [u_pressure]
    type = INSFVMomentumPressure
    variable = u
    momentum_component = 'x'
    p = pressure
  []
  [u_forcing]
    type = FVBodyForce
    variable = u
    function = forcing_u
  []

  [v_advection]
    type = INSFVMomentumAdvection
    variable = v
    advected_quantity = 'rhov'
    vel = 'velocity'
    advected_interp_method = 'average'
    velocity_interp_method = 'rc'
    pressure = pressure
    u = u
    v = v
    mu = ${mu}
    rho = ${rho}
    no_slip_wall_boundaries = 'left right top bottom'
  []
  [v_viscosity]
    type = FVDiffusion
    variable = v
    coeff = ${mu}
  []
  [v_pressure]
    type = INSFVMomentumPressure
    variable = v
    momentum_component = 'y'
    p = pressure
  []
  [v_forcing]
    type = FVBodyForce
    variable = v
    function = forcing_v
  []
[]

[FVBCs]
  [no-slip-wall-u]
    type = INSFVNoSlipWallBC
    boundary = 'left right top bottom'
    variable = u
    function = 'exact_u'
  []

  [no-slip-wall-v]
    type = INSFVNoSlipWallBC
    boundary = 'left right top bottom'
    variable = v
    function = 'exact_v'
  []
[]

[Materials]
  [ins_fv]
    type = INSFVMaterial
    u = u
    v = v
    pressure = 'pressure'
    rho = ${rho}
  []
[]

[Functions]
[exact_u]
  type = ParsedFunction
  value = 'sin(y)*sin(x*pi)'
[]
[exact_rhou]
  type = ParsedFunction
  value = 'rho*sin(y)*sin(x*pi)'
  vars = 'rho'
  vals = '${rho}'
[]
[forcing_u]
  type = ParsedFunction
  value = 'mu*sin(y)*sin(x*pi) - (-x*pi^2*mu*sin(y)*sin(x*pi) + pi*mu*sin(y)*cos(x*pi))/x + (2*x*pi*rho*sin(y)^2*sin(x*pi)*cos(x*pi) + rho*sin(y)^2*sin(x*pi)^2)/x + (-1/2*x*pi*rho*sin(x)*sin(y)*sin(x*pi)*sin((1/2)*y*pi) + x*rho*sin(x)*sin(x*pi)*cos(y)*cos((1/2)*y*pi))/x'
  vars = 'mu rho'
  vals = '${mu} ${rho}'
[]
[exact_v]
  type = ParsedFunction
  value = 'sin(x)*cos((1/2)*y*pi)'
[]
[exact_rhov]
  type = ParsedFunction
  value = 'rho*sin(x)*cos((1/2)*y*pi)'
  vars = 'rho'
  vals = '${rho}'
[]
[forcing_v]
  type = ParsedFunction
  value = '(1/4)*pi^2*mu*sin(x)*cos((1/2)*y*pi) - pi*rho*sin(x)^2*sin((1/2)*y*pi)*cos((1/2)*y*pi) + cos(y) - (-x*mu*sin(x)*cos((1/2)*y*pi) + mu*cos(x)*cos((1/2)*y*pi))/x + (x*pi*rho*sin(x)*sin(y)*cos(x*pi)*cos((1/2)*y*pi) + x*rho*sin(y)*sin(x*pi)*cos(x)*cos((1/2)*y*pi) + rho*sin(x)*sin(y)*sin(x*pi)*cos((1/2)*y*pi))/x'
  vars = 'mu rho'
  vals = '${mu} ${rho}'
[]
[exact_p]
  type = ParsedFunction
  value = 'sin(y)'
[]
[forcing_p]
  type = ParsedFunction
  value = '-1/2*pi*rho*sin(x)*sin((1/2)*y*pi) + (x*pi*rho*sin(y)*cos(x*pi) + rho*sin(y)*sin(x*pi))/x'
  vars = 'rho'
  vals = '${rho}'
[]
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_pc_type -sub_pc_factor_shift_type'
  petsc_options_value = 'asm      30                 lu           NONZERO'
  nl_rel_tol = 1e-12
[]

[Outputs]
  exodus = true
  csv = true
[]

[Postprocessors]
  [h]
    type = AverageElementSize
    outputs = 'console csv'
    execute_on = 'timestep_end'
  []
  [./L2u]
    type = ElementL2Error
    variable = u
    function = exact_u
    outputs = 'console csv'
    execute_on = 'timestep_end'
  [../]
  [./L2v]
    type = ElementL2Error
    variable = v
    function = exact_v
    outputs = 'console csv'
    execute_on = 'timestep_end'
  [../]
  [./L2p]
    variable = pressure
    function = exact_p
    type = ElementL2Error
    outputs = 'console csv'
    execute_on = 'timestep_end'
  [../]
[]
