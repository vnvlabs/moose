mu=1.1
rho=1.1

[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
    xmin = 0
    xmax = 5
    ymin = -1
    ymax = 1
    nx = 50
    ny = 10
  []
[]

[Modules]
  [NavierStokesFV]
    compressibility = 'incompressible'

    density = 'rho'
    dynamic_viscosity = 'mu'

    initial_velocity = '1 1 0'
    initial_pressure = 0.0

    inlet_boundaries = 'left'
    momentum_inlet_types = 'fixed-velocity'
    momentum_inlet_function = '1 0'
    wall_boundaries = 'top bottom'
    momentum_wall_types = 'noslip noslip'
    outlet_boundaries = 'right'
    momentum_outlet_types = 'fixed-pressure'
    pressure_function = '0'

    friction_types = 'darcy'
    friction_coeffs = '25'
  []
[]

[Materials]
  [const]
    type = ADGenericFunctorMaterial
    prop_names = 'rho mu'
    prop_values = '${rho} ${mu}'
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

[Outputs]
  exodus = true
[]
