CDF      
      len_name      	time_step          num_dim       	num_nodes         num_elem      
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1        num_nod_per_el1       num_side_ss1      num_side_ss2      num_nod_ns1       num_nod_ns2       num_elem_var      num_info  �   len_line   Q         api_version       A   version       A   floating_point_word_size            	file_size               maximum_name_length              int64_status             title         test_out.e           
time_whole                            ��   	eb_status                             0   eb_prop1               name      ID              4   	ns_status                             8   ns_prop1               name      ID              @   	ss_status                             H   ss_prop1               name      ID              P   coordx                      �      X   coordy                      �      	    coordz                      �      	�   eb_names                   
_FillValue                        
P   ns_names                   
_FillValue                        P   ss_names                   
_FillValue                        P   
coor_names                     
_FillValue                        P   node_num_map                    T      P   connect1         	         	elem_type         EDGE2         �      �   elem_num_map                    P      D   elem_ss1      
                    �   side_ss1      
                    �   elem_ss2                          �   side_ss2                          �   node_ns1                          �   node_ns2                          �   name_elem_var                      
_FillValue                        �   vals_elem_var1eb1                          �      ��   elem_var_tab                             �   info_records                      {      �                                         ?�������?�������?�333333?ə�����?�      ?�333333?�ffffff?ٙ�����?�������?�      ?ᙙ����?�333333?�������?�ffffff?�      ?陙����?�333333?�������?�ffffff?�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      left                                                                                                                                                                                                                                                            right                                                                                                                                                                                                                                                           left                                                                                                                                                                                                                                                            right                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      	   
                                                                                 	   	   
   
                                                                                          	   
                                                u                                                                                                                                                                                                                                                                  #################### �      ?�      ?�      ?�      ?�      ?�      ?�      ?�   # Created by MOOSE #                                                             ####################                                                             ### Command Line Arguments ###                                                    ../../../moose_test-dbg -i test.i### Version Info ###                           Framework Information:                                                           MOOSE Version:           git commit b828f087f7 on 2023-03-30                     LibMesh Version:         14633497ea867c56053d1ea7a1fbe0442727eb24                PETSc Version:           3.16.6                                                  SLEPc Version:           3.16.2                                                  Current Time:            Thu Mar 30 16:50:32 2023                                Executable Timestamp:    Thu Mar 30 16:48:45 2023                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 _unique_action_name            = AddRelationshipManager                          control_tags                   = INVALID                                         inactive                       = (no_default)                                    initial_from_file_timestep     = LATEST                                          initial_from_file_var          = INVALID                                         allow_negative_qweights        = 1                                               custom_blocks                  = (no_default)                                    custom_orders                  = (no_default)                                    element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [Executioner]                                                                      _unique_action_name            = CreateExecutionerActionExecutioner              auto_preconditioning           = 1                                               control_tags                   = INVALID                                         inactive                       = (no_default)                                    isObjectAction                 = 1                                               type                           = Steady                                          accept_on_max_fixed_point_iteration = 0                                          accept_on_max_picard_iteration = 0                                               auto_advance                   = INVALID                                         automatic_scaling              = INVALID                                         compute_initial_residual_before_preset_bcs = 0                                   compute_scaling_once           = 1                                               contact_line_search_allowed_lambda_cuts = 2                                      contact_line_search_ltol       = INVALID                                         custom_abs_tol                 = 1e-50                                           custom_pp                      = INVALID                                         custom_rel_tol                 = 1e-08                                           direct_pp_value                = 0                                               disable_fixed_point_residual_norm_check = 0                                      disable_picard_residual_norm_check = 0                                           enable                         = 1                                               fixed_point_abs_tol            = 1e-50                                           fixed_point_algorithm          = picard                                          fixed_point_force_norms        = 0                                               fixed_point_max_its            = 1                                               fixed_point_min_its            = 1                                               fixed_point_rel_tol            = 1e-08                                           ignore_variables_for_autoscaling = INVALID                                       l_abs_tol                      = 1e-50                                           l_max_its                      = 10000                                           l_tol                          = 1e-05                                           line_search                    = none                                            line_search_package            = petsc                                           max_xfem_update                = 4294967295                                      mffd_type                      = wp                                              n_max_nonlinear_pingpong       = 100                                             nl_abs_div_tol                 = 1e+50                                           nl_abs_step_tol                = 0                                               nl_abs_tol                     = 1e-50                                           nl_div_tol                     = 1e+10                                           nl_forced_its                  = 0                                               nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 0                                               nl_rel_tol                     = 1e-12                                           num_grids                      = 1                                               off_diagonals_in_auto_scaling  = 0                                               outputs                        = INVALID                                         petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         picard_abs_tol                 = 1e-50                                           picard_custom_pp               = INVALID                                         picard_force_norms             = 0                                               picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           relaxation_factor              = 1                                               relaxed_variables              = (no_default)                                    resid_vs_jac_scaling_param     = 0                                               residual_and_jacobian_together = 0                                               restart_file_base              = (no_default)                                    reuse_preconditioner           = 0                                               reuse_preconditioner_max_linear_its = 25                                         scaling_group_variables        = INVALID                                         skip_exception_check           = 0                                               snesmf_reuse_base              = 1                                               solve_type                     = NEWTON                                          splitting                      = INVALID                                         time                           = 0                                               transformed_postprocessors     = (no_default)                                    transformed_variables          = (no_default)                                    update_xfem_at_timestep_begin  = 0                                               verbose                        = 0                                             []                                                                                                                                                                [FVBCs]                                                                            _unique_action_name            = CheckFVBCActionFVBCs                            control_tags                   = (no_default)                                    inactive                       = (no_default)                                                                                                                     [./left]                                                                           _unique_action_name          = AddFVBCActionFVBCs/left                           control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = FVDirichletBC                                     absolute_value_vector_tags   = INVALID                                           boundary                     = left                                              displacements                = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 matrix_tags                  = system                                            use_displaced_mesh           = 0                                                 value                        = 0                                                 variable                     = u                                                 vector_tags                  = nontime                                         [../]                                                                                                                                                             [./right]                                                                          _unique_action_name          = AddFVBCActionFVBCs/right                          control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = FVDirichletBC                                     absolute_value_vector_tags   = INVALID                                           boundary                     = right                                             displacements                = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 matrix_tags                  = system                                            use_displaced_mesh           = 0                                                 value                        = 1                                                 variable                     = u                                                 vector_tags                  = nontime                                         [../]                                                                          []                                                                                                                                                                [FVKernels]                                                                                                                                                         [./diff]                                                                           _unique_action_name          = AddFVKernelActionFVKernels/diff                   control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = FVDiffusion                                       absolute_value_vector_tags   = INVALID                                           block                        = INVALID                                           boundaries_to_avoid          = (no_default)                                      boundaries_to_force          = (no_default)                                      coeff                        = 1                                                 coeff_interp_method          = harmonic                                          enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           force_boundary_execution     = 0                                                 ghost_layers                 = 2                                                 implicit                     = 1                                                 matrix_tags                  = system                                            prop_getter_suffix           = (no_default)                                      seed                         = 0                                                 use_displaced_mesh           = 0                                                 use_point_neighbors          = 0                                                 variable                     = u                                                 vector_tags                  = nontime                                         [../]                                                                                                                                                             [./rxn]                                                                            _unique_action_name          = AddFVKernelActionFVKernels/rxn                    control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = FVSecondOrderRxnLagged                            absolute_value_vector_tags   = INVALID                                           block                        = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           ghost_layers                 = 1                                                 implicit                     = 1                                                 lag                          = 0                                                 matrix_tags                  = system                                            prop_getter_suffix           = (no_default)                                      seed                         = 0                                                 use_displaced_mesh           = 0                                                 use_point_neighbors          = 0                                                 variable                     = u                                                 vector_tags                  = nontime                                         [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             _unique_action_name            = CreateDisplacedProblemActionMesh                control_tags                   = (no_default)                                    displacements                  = INVALID                                         inactive                       = (no_default)                                    use_displaced_mesh             = 1                                               include_local_in_ghosting      = 0                                               output_ghosting                = 0                                               block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         isObjectAction                 = 1                                               second_order                   = 0                                               skip_deletion_repartition_after_refine = 0                                       skip_partitioning              = 0                                               type                           = GeneratedMesh                                   uniform_refine                 = 0                                               add_subdomain_ids              = INVALID                                         allow_renumbering              = 1                                               alpha_rotation                 = INVALID                                         beta_rotation                  = INVALID                                         bias_x                         = 1                                               bias_y                         = 1                                               bias_z                         = 1                                               block                          = INVALID                                         build_all_side_lowerd_mesh     = 0                                               centroid_partitioner_direction = INVALID                                         construct_node_list_from_side_list = 1                                           coord_block                    = INVALID                                         coord_type                     = XYZ                                             dim                            = 1                                               elem_type                      = INVALID                                         enable                         = 1                                               gamma_rotation                 = INVALID                                         gauss_lobatto_grid             = 0                                               ghosting_patch_size            = INVALID                                         length_unit                    = INVALID                                         max_leaf_size                  = 10                                              nemesis                        = 0                                               nx                             = 20                                              ny                             = 1                                               nz                             = 1                                               parallel_type                  = DEFAULT                                         partitioner                    = default                                         patch_size                     = 40                                              patch_update_strategy          = never                                           rz_coord_axis                  = Y                                               skip_refine_when_use_split     = 1                                               up_direction                   = INVALID                                         xmax                           = 1                                               xmin                           = 0                                               ymax                           = 1                                               ymin                           = 0                                               zmax                           = 1                                               zmin                           = 0                                             []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Outputs]                                                                          _unique_action_name            = CommonOutputActionOutputs                       append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               control_tags                   = (no_default)                                    controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         inactive                       = (no_default)                                    interval                       = 1                                               json                           = 0                                               minimum_time_interval          = 0                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         perf_graph                     = 0                                               perf_graph_live                = 1                                               perf_graph_live_mem_limit      = 100                                             perf_graph_live_time_limit     = 5                                               print_linear_converged_reason  = 1                                               print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_nonlinear_converged_reason = 1                                             print_nonlinear_residuals      = 1                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     = (no_default)                                    tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                               xml                            = 0                                             []                                                                                                                                                                [Problem]                                                                          _unique_action_name            = CreateProblemActionProblem                      control_tags                   = INVALID                                         inactive                       = (no_default)                                    isObjectAction                 = 1                                               name                           = 'MOOSE Problem'                                 type                           = FEProblem                                       library_name                   = (no_default)                                    library_path                   = (no_default)                                    object_names                   = INVALID                                         register_objects_from          = INVALID                                         allow_invalid_solution         = 0                                               block                          = INVALID                                         boundary_restricted_elem_integrity_check = 1                                     boundary_restricted_node_integrity_check = 1                                     check_uo_aux_state             = 0                                               coord_type                     = XYZ                                             default_ghosting               = 0                                               enable                         = 1                                               error_on_jacobian_nonzero_reallocation = INVALID                                 extra_tag_matrices             = INVALID                                         extra_tag_solutions            = INVALID                                         extra_tag_vectors              = INVALID                                         force_restart                  = 0                                               fv_bcs_integrity_check         = 1                                               ignore_zeros_in_jacobian       = 0                                               immediately_print_invalid_solution = 0                                           kernel_coverage_check          = 1                                               material_coverage_check        = 1                                               material_dependency_check      = 1                                               near_null_space_dimension      = 0                                               nl_sys_names                   = nl0                                             null_space_dimension           = 0                                               parallel_barrier_messaging     = 0                                               previous_nl_solution_required  = 1                                               restart_file_base              = INVALID                                         rz_coord_axis                  = Y                                               skip_additional_restart_data   = 0                                               skip_nl_system_check           = 0                                               solve                          = 1                                               transpose_null_space_dimension = 0                                               use_nonlinear                  = 1                                               verbose_multiapps              = 0                                             []                                                                                                                                                                [Variables]                                                                                                                                                         [./u]                                                                              _unique_action_name          = AddVariableActionVariables/u                      control_tags                 = INVALID                                           family                       = LAGRANGE                                          inactive                     = (no_default)                                      initial_condition            = 1                                                 isObjectAction               = 1                                                 order                        = FIRST                                             scaling                      = INVALID                                           type                         = MooseVariableFVReal                               initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                           array                        = 0                                                 block                        = INVALID                                           cache_cell_gradients         = 1                                                 components                   = 1                                                 eigen                        = 0                                                 enable                       = 1                                                 face_interp_method           = average                                           fv                           = 1                                                 nl_sys                       = nl0                                               outputs                      = INVALID                                           two_term_boundary_expansion  = 1                                                 use_dual                     = 0                                               [../]                                                                          []                                                                                          ?�     ?�     ?�     ?�������?�     ?�     ?�     ?�      ?�     ?�     ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�� ��?���1�{?������?ļ
���H?ʫ�mآ�?�O}m�y@?�K�/��?�K�9�?�Pª��?�\%�tH?�o��ϖ<?�Fq�'�?���׫5?�v�D�Z?��*�?������?�����?�H5��.�?�N�N�r?�[W���