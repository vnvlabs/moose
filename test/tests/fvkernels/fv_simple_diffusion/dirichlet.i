[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [u]
  []
  [v]
    family = MONOMIAL
    order = CONSTANT
    fv = true
  []
[]

[Kernels]
  [diff]
    type = Diffusion
    variable = u
  []
[]

[FVKernels]
  [diff]
    type = FVDiffusion
    variable = v
    coeff = coeff
  []
[]

[FVBCs]
  [left]
    type = FVDirichletBC
    variable = v
    boundary = left
    value = 7
  []
  [right]
    type = FVDirichletBC
    variable = v
    boundary = right
    value = 42
  []
[]

[Materials]
  [diff]
    type = ADGenericFunctorMaterial
    prop_names = 'coeff'
    prop_values = '1'
  []
[]

[BCs]
  [left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 7
  []
  [right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 42
  []
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]
