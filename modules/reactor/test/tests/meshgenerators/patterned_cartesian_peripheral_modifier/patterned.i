new_num_sector = 10
num_layer = 2

[Mesh]
  [sq_1]
    type = PolygonConcentricCircleMeshGenerator
    num_sides = 4
    num_sectors_per_side = '2 2 2 2'
    background_intervals = 1
    ring_radii = 4.0
    ring_intervals = 1
    ring_block_ids = '10'
    ring_block_names = 'center_1'
    background_block_ids = 20
    background_block_names = background_1
    polygon_size = 5.0
    preserve_volumes = on
    quad_center_elements = true
    flat_side_up = true
  []
  [pattern_1]
    type = PatternedCartesianMeshGenerator
    inputs = 'sq_1'
    pattern = '0 0 0;
               0 0 0;
               0 0 0'
    background_intervals = 1
    square_size = 34
  []
  [pmg_1]
    type = PatternedCartesianPeripheralModifier
    input = pattern_1
    input_mesh_external_boundary = 10000
    new_num_sector = ${new_num_sector}
    num_layers = ${num_layer}
  []
  [sq_2]
    type = PolygonConcentricCircleMeshGenerator
    num_sides = 4
    num_sectors_per_side = '2 2 2 2'
    background_intervals = 1
    ring_radii = 2.5
    ring_intervals = 1
    ring_block_ids = '30'
    ring_block_names = 'center_2'
    background_block_ids = 40
    background_block_names = background_2
    polygon_size = 3.0
    preserve_volumes = on
    quad_center_elements = true
    flat_side_up = true
  []
  [pattern_2]
    type = PatternedCartesianMeshGenerator
    inputs = 'sq_2'
    pattern = '0 0 0 0;
               0 0 0 0;
               0 0 0 0;
               0 0 0 0'
    background_intervals = 1
    square_size = 34
  []
  [pmg_2]
    type = PatternedCartesianPeripheralModifier
    input = pattern_2
    input_mesh_external_boundary = 10000
    new_num_sector = ${new_num_sector}
    num_layers = ${num_layer}
  []
  [sq_3]
    type = PolygonConcentricCircleMeshGenerator
    num_sides = 4
    num_sectors_per_side = '2 2 2 2'
    background_intervals = 1
    ring_radii = 1.5
    ring_intervals = 1
    ring_block_ids = '50'
    ring_block_names = 'center_3'
    background_block_ids = 60
    background_block_names = background_3
    polygon_size = 2.3
    preserve_volumes = on
    quad_center_elements = true
    flat_side_up = true
  []
  [pattern_3]
    type = PatternedCartesianMeshGenerator
    inputs = 'sq_3'
    pattern = '0 0 0 0 0;
               0 0 0 0 0;
               0 0 0 0 0;
               0 0 0 0 0;
               0 0 0 0 0'
    background_intervals = 1
    square_size = 34
  []
  [pmg_3]
    type = PatternedCartesianPeripheralModifier
    input = pattern_3
    input_mesh_external_boundary = 10000
    new_num_sector = ${new_num_sector}
    num_layers = ${num_layer}
  []
  [sq_4]
    type = PolygonConcentricCircleMeshGenerator
    num_sides = 4
    num_sectors_per_side = '2 2 2 2'
    background_intervals = 1
    ring_radii = 1.4
    ring_intervals = 1
    ring_block_ids = '70'
    ring_block_names = 'center_4'
    background_block_ids = 80
    background_block_names = background_4
    polygon_size = 1.8
    preserve_volumes = on
    quad_center_elements = true
    flat_side_up = true
  []
  [pattern_4]
    type = PatternedCartesianMeshGenerator
    inputs = 'sq_4'
    pattern = '0 0 0 0 0 0;
               0 0 0 0 0 0;
               0 0 0 0 0 0;
               0 0 0 0 0 0;
               0 0 0 0 0 0;
               0 0 0 0 0 0'
    background_intervals = 1
    square_size = 34
  []
  [pmg_4]
    type = PatternedCartesianPeripheralModifier
    input = pattern_4
    input_mesh_external_boundary = 10000
    new_num_sector = ${new_num_sector}
    num_layers = ${num_layer}
  []
  [pattern_sum]
    type = PatternedCartesianMeshGenerator
    inputs = 'pmg_1 pmg_2 pmg_3 pmg_4'
    pattern = '1 2 3;
               2 0 2;
               3 2 1'
    pattern_boundary = none
    generate_core_metadata = true
  []
[]

[Outputs]
  [out]
    type = Exodus
    output_extra_element_ids = false
  []
[]
