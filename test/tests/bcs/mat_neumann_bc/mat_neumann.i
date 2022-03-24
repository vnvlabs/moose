[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 10
  ymax = 10
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
[]

[ICs]
  [./phi_IC]
    type = FunctionIC
    variable = phi
    function = ic_func_phi
  [../]
[]

[Functions]
  [./ic_func_phi]
    type = ParsedFunction
    value = '0.5 * (1 - tanh((x - 5) / 0.8))'
  [../]
[]

[BCs]
  [./top]
    type = MatNeumannBC
    variable = u
    boundary = top
    value = 2
    boundary_material = hm
  [../]
[]

[Kernels]
  [./dudt]
    type = TimeDerivative
    variable = u
  [../]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[Materials]
  [./hm]
    type = ParsedMaterial
    f_name = hm
    args = 'phi'
    function = '3*phi^2 - 2*phi^3'
    outputs = exodus
  [../]
[]

[Executioner]
  type = Transient

  solve_type = 'PJFNK'
  end_time = 10
[]

[Outputs]
  exodus = true
[]

