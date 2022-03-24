#
# This test validates the error checking for required coupled
# material properties within ParsedMaterials and DerivativeParsedMaterials
#

[Mesh]
  type = GeneratedMesh
  dim = 1
[]

[Variables]
  [c]
  []
[]

[Materials]
  [prime]
    type = DerivativeParsedMaterial
    function = Q
    f_name = P
  []
  [second]
    type = DerivativeParsedMaterial
    function = c
    derivative_order = 1
    args = c
    f_name = S
  []
[]

[Postprocessors]
  [avg]
    type = ElementAverageMaterialProperty
    mat_prop = P
  []
[]

[Problem]
  kernel_coverage_check = false
[]

[Executioner]
  type = Transient
  num_steps = 1
  solve_type = NEWTON
[]

[Outputs]
  csv = true
[]
