CDF      
      len_name      	time_step          num_dim       	num_nodes         num_elem      
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1        num_nod_per_el1       num_el_in_blk2        num_nod_per_el2       num_side_ss1      num_side_ss2      num_side_ss3      num_side_ss4      num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4    	   num_nod_var       num_elem_var      num_info  x   len_line   Q         api_version       AÂ   version       AÂ   floating_point_word_size            	file_size               maximum_name_length              int64_status             title         corner_wrap_out.e         &   
time_whole                               	eb_status                             4   eb_prop1               name      ID              <   	ns_status                             D   ns_prop1               name      ID              T   	ss_status                             d   ss_prop1               name      ID              t   coordx                      ð         coordy                      ð      t   eb_names                   
_FillValue                        d   ns_names                   
_FillValue                        d   ss_names                   
_FillValue                        d   
coor_names                     
_FillValue                        d   node_num_map                    x      d   connect1         	         	elem_type         SHELL4        @      Ü   connect2      
            	elem_type         SHELL4        À         elem_num_map                    @      Ü   elem_ss1                             side_ss1                          ,   elem_ss2                          <   side_ss2                          D   elem_ss3                          L   side_ss3                          \   elem_ss4                           l   side_ss4                              node_ns1                          ¬   node_ns2                          ¸   node_ns3                          Ì   node_ns4                    $      à   name_nod_var                   
_FillValue                           vals_nod_var1                          ð         name_elem_var                      
_FillValue                           vals_elem_var1eb1                                    vals_elem_var2eb1                                 $   vals_elem_var1eb2            
              `      D   vals_elem_var2eb2            
              `      ¤   elem_var_tab                                info_records                      vø                                                                  ?ð      ?à      ?à      ?ð                      ?à      ?ð              ¿¹¿á¿á¿¹¿ð      ¿ð      ¿á¿¹¿ð      ¿á¿ð      ¿¹¿á¿ð      ¿¹ ?ÜÌÌÌÌÌÌ?ÜÌÌÌÌÌÌ?ð      ?ð      ?ÜÌÌÌÌÌÌ?ð                      ¿à      ¿à              ¿à      ¿ð      ¿ð      ¿ð      ?¹?¹¿ÜÌÌÌÌÌÎ¿ÜÌÌÌÌÌÎ?¹¿ÜÌÌÌÌÌÐ¿ð      ¿ð      ¿ð      ?á?á?á?ð      ?ð      ?ð      ?¹?á?¹ ?á?ð      ?ð                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 	   
                                                                                                         	      
                                                               
                                 
                                                                        	   
                                                                                       	                                                               	   
                                       temp                                                                                                                                                                                                                                                            paired_temp                                                                                                                                                                                                                                                     qpoint_penetration                                                                                                                                                                                                                                                          #################### Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y   # Created by MOOSE #       @Y      @Y      @Y      @Y      @Y      @Y      @Y    ####################      @Y      ¿¹¿¹        ¿¹@I             ### Command Line Arguments ###                   @Y      @Y                       /Users/spenbw/gitproj/githerd/moose/modules/heat_conduction/heat_conduction-... opt -i corner_wrap.i --error --error-override --no-gdb-backtrace### Version I... nfo ###                                                                          Framework Information:                                                           MOOSE Version:           git commit 962be8fe83 on 2023-02-17                     LibMesh Version:                                                                 PETSc Version:           3.16.6                                                  SLEPc Version:           3.16.2                                                  Current Time:            Fri Feb 17 17:16:10 2023                                Executable Timestamp:    Fri Feb 17 16:55:01 2023                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 _unique_action_name            = AddRelationshipManager                          control_tags                   = INVALID                                         inactive                       = (no_default)                                    initial_from_file_timestep     = LATEST                                          initial_from_file_var          = INVALID                                         allow_negative_qweights        = 1                                               custom_blocks                  = (no_default)                                    custom_orders                  = (no_default)                                    element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [BCs]                                                                                                                                                               [./temp_bot_right]                                                                 _unique_action_name          = AddBCActionadd_bcBCs/temp_bot_right               control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = DirichletBC                                       boundary                     = 1                                                 diag_save_in                 = INVALID                                           displacements                = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 matrix_tags                  = 'system time'                                     preset                       = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 value                        = 50                                                variable                     = temp                                              vector_tags                  = residual                                        [../]                                                                                                                                                             [./temp_top_left]                                                                  _unique_action_name          = AddBCActionadd_bcBCs/temp_top_left                control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = DirichletBC                                       boundary                     = 4                                                 diag_save_in                 = INVALID                                           displacements                = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 matrix_tags                  = 'system time'                                     preset                       = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 value                        = 100                                               variable                     = temp                                              vector_tags                  = residual                                        [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      _unique_action_name            = CreateExecutionerActionExecutioner              auto_preconditioning           = 1                                               control_tags                   = INVALID                                         inactive                       = (no_default)                                    isObjectAction                 = 1                                               type                           = Steady                                          accept_on_max_fixed_point_iteration = 0                                          accept_on_max_picard_iteration = 0                                               auto_advance                   = INVALID                                         automatic_scaling              = INVALID                                         compute_initial_residual_before_preset_bcs = 0                                   compute_scaling_once           = 1                                               contact_line_search_allowed_lambda_cuts = 2                                      contact_line_search_ltol       = INVALID                                         custom_abs_tol                 = 1e-50                                           custom_pp                      = INVALID                                         custom_rel_tol                 = 1e-08                                           direct_pp_value                = 0                                               disable_fixed_point_residual_norm_check = 0                                      disable_picard_residual_norm_check = 0                                           enable                         = 1                                               fixed_point_abs_tol            = 1e-50                                           fixed_point_algorithm          = picard                                          fixed_point_force_norms        = 0                                               fixed_point_max_its            = 1                                               fixed_point_min_its            = 1                                               fixed_point_rel_tol            = 1e-08                                           ignore_variables_for_autoscaling = INVALID                                       l_abs_tol                      = 1e-50                                           l_max_its                      = 100                                             l_tol                          = 0.001                                           line_search                    = none                                            line_search_package            = petsc                                           max_xfem_update                = 4294967295                                      mffd_type                      = wp                                              n_max_nonlinear_pingpong       = 100                                             nl_abs_div_tol                 = 1e+50                                           nl_abs_step_tol                = 0                                               nl_abs_tol                     = 1e-50                                           nl_div_tol                     = 1e+10                                           nl_forced_its                  = 0                                               nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 0                                               nl_rel_tol                     = 1e-14                                           num_grids                      = 1                                               off_diagonals_in_auto_scaling  = 0                                               outputs                        = INVALID                                         petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         picard_abs_tol                 = 1e-50                                           picard_custom_pp               = INVALID                                         picard_force_norms             = 0                                               picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           relaxation_factor              = 1                                               relaxed_variables              = (no_default)                                    resid_vs_jac_scaling_param     = 0                                               residual_and_jacobian_together = 0                                               restart_file_base              = (no_default)                                    reuse_preconditioner           = 0                                               reuse_preconditioner_max_linear_its = 25                                         scaling_group_variables        = INVALID                                         skip_exception_check           = 0                                               snesmf_reuse_base              = 1                                               solve_type                     = PJFNK                                           splitting                      = INVALID                                         time                           = 0                                               transformed_postprocessors     = (no_default)                                    transformed_variables          = (no_default)                                    update_xfem_at_timestep_begin  = 0                                               verbose                        = 0                                             []                                                                                                                                                                [Kernels]                                                                                                                                                           [./heat]                                                                           _unique_action_name          = AddKernelActionadd_kernelKernels/heat             control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = HeatConduction                                    block                        = INVALID                                           diag_save_in                 = INVALID                                           diffusion_coefficient        = thermal_conductivity                              diffusion_coefficient_dT     = thermal_conductivity_dT                           displacements                = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 matrix_tags                  = system                                            prop_getter_suffix           = (no_default)                                      save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = temp                                              vector_tags                  = nontime                                         [../]                                                                          []                                                                                                                                                                [Materials]                                                                                                                                                         [./heat1]                                                                          _unique_action_name          = AddMaterialActionMaterials/heat1                  control_tags                 = INVALID                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = HeatConductionMaterial                            block                        = '1 2'                                             boundary                     = INVALID                                           compute                      = 1                                                 constant_on                  = NONE                                              declare_suffix               = (no_default)                                      enable                       = 1                                                 implicit                     = 1                                                 output_properties            = INVALID                                           outputs                      = none                                              prop_getter_suffix           = (no_default)                                      seed                         = 0                                                 specific_heat                = 1                                                 specific_heat_temperature_function = (no_default)                                temp                         = INVALID                                           thermal_conductivity         = 1                                                 thermal_conductivity_temperature_function = (no_default)                         use_displaced_mesh           = 0                                               [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             _unique_action_name            = CreateDisplacedProblemActionMesh                control_tags                   = (no_default)                                    displacements                  = INVALID                                         inactive                       = (no_default)                                    use_displaced_mesh             = 1                                               include_local_in_ghosting      = 0                                               output_ghosting                = 0                                               block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         isObjectAction                 = 1                                               second_order                   = 0                                               skip_deletion_repartition_after_refine = 0                                       skip_partitioning              = 0                                               type                           = FileMesh                                        uniform_refine                 = 0                                               allow_renumbering              = 1                                               alpha_rotation                 = INVALID                                         beta_rotation                  = INVALID                                         block                          = INVALID                                         build_all_side_lowerd_mesh     = 0                                               centroid_partitioner_direction = INVALID                                         clear_spline_nodes             = 0                                               construct_node_list_from_side_list = 1                                           coord_block                    = INVALID                                         coord_type                     = XYZ                                             dim                            = 1                                               enable                         = 1                                               file                           = /Users/spenbw/gitproj/githerd/moose/module... s/heat_conduction/test/tests/gap_heat_transfer_htonly/corner_wrap.e                gamma_rotation                 = INVALID                                         ghosting_patch_size            = INVALID                                         length_unit                    = INVALID                                         max_leaf_size                  = 10                                              nemesis                        = 0                                               parallel_type                  = DEFAULT                                         partitioner                    = default                                         patch_size                     = 40                                              patch_update_strategy          = never                                           rz_coord_axis                  = Y                                               skip_refine_when_use_split     = 1                                               up_direction                   = INVALID                                       []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Outputs]                                                                          _unique_action_name            = CommonOutputActionOutputs                       append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               control_tags                   = (no_default)                                    controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         inactive                       = (no_default)                                    interval                       = 1                                               json                           = 0                                               minimum_time_interval          = 0                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         perf_graph                     = 0                                               perf_graph_live                = 1                                               perf_graph_live_mem_limit      = 100                                             perf_graph_live_time_limit     = 5                                               print_linear_converged_reason  = 1                                               print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_nonlinear_converged_reason = 1                                             print_nonlinear_residuals      = 1                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     = (no_default)                                    tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                               xml                            = 0                                             []                                                                                                                                                                [ThermalContact]                                                                                                                                                    [./thermal_contact]                                                                _unique_action_name          = ThermalContactActionadd_aux_kernelThermalC... ontact/thermal_contact                                                               appended_property_name       = (no_default)                                      check_boundary_restricted    = 0                                                 control_tags                 = ThermalContact                                    cylinder_axis_point_1        = INVALID                                           cylinder_axis_point_2        = INVALID                                           displacements                = INVALID                                           emissivity_primary           = 0                                                 emissivity_secondary         = 0                                                 gap_aux_type                 = GapValueAux                                       gap_conductance              = 0                                                 gap_conductivity             = 1                                                 gap_conductivity_function    = INVALID                                           gap_conductivity_function_variable = INVALID                                     gap_geometry_type            = INVALID                                           inactive                     = (no_default)                                      mapped_primary_gap_offset    = INVALID                                           max_gap                      = 1e+06                                             min_gap                      = 1e-06                                             min_gap_order                = 0                                                 normal_smoothing_distance    = INVALID                                           normal_smoothing_method      = INVALID                                           order                        = FIRST                                             primary                      = 3                                                 quadrature                   = 1                                                 save_in                      = INVALID                                           secondary                    = 2                                                 secondary_gap_offset         = INVALID                                           sphere_origin                = INVALID                                           tangential_tolerance         = INVALID                                           type                         = GapHeatTransfer                                   variable                     = temp                                              warnings                     = 0                                               [../]                                                                          []                                                                                                                                                                [Variables]                                                                                                                                                         [./temp]                                                                           _unique_action_name          = AddVariableActionVariables/temp                   control_tags                 = INVALID                                           family                       = LAGRANGE                                          inactive                     = (no_default)                                      initial_condition            = 100                                               isObjectAction               = 1                                                 order                        = FIRST                                             scaling                      = INVALID                                           type                         = MooseVariableBase                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                           array                        = 0                                                 block                        = INVALID                                           components                   = 1                                                 eigen                        = 0                                                 enable                       = 1                                                 fv                           = 0                                                 nl_sys                       = nl0                                               outputs                      = INVALID                                           use_dual                     = 0                                               [../]                                                                          []                                                                                       @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y              @Y      ¿¹¿¹        ¿¹@I              @Y                                              @Y      @Y                                                                                                                      ?ð      @SI}@SèÃº@QSeÊXk@I      @V®UÆ@T^·QW@I      @I      @SwûfÄ[@Vª9çìÝ@WÖöl+@W3D¹3B@UWåEÜÛ¡@Y      @Y      @Vëü95#¤@T@½ã@Y      @Xhj[×àæ@Y      @WÂ"<ÿ @Y      @Y      @Y      @T¯cÕ`@W	<iÿ_@SñBð¿@V¶Ýd»@Y      @Y      @TG®+p:Ò@UÒìÆÜ&        @T¦ÑXÉ@Ì¿¹¿¹        ¿¹@F¡W@        @Söâ÷Î³                                        @UNÜßJ@S¡"-¾                                                                                                                