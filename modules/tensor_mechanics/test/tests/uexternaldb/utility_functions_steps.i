[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
  []
[]

[Problem]
  solve = false
  kernel_coverage_check = false
[]

[UserObjects]
  [step_uo]
   type = StepUserObject
   number_steps = 2
   times = '0 1'
  []
  [uexternaldb]
    type = AbaqusUExternalDB
    plugin = ../../plugins/utility_functions
    step_user_object = step_uo
    execute_on = 'INITIAL TIMESTEP_END TIMESTEP_BEGIN FINAL'
  []
[]

[Executioner]
  type = Transient
  num_steps = 2
[]
