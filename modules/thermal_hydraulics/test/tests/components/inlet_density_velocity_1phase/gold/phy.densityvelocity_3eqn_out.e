CDF      
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes         num_elem   
   
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1     
   num_nod_per_el1       num_side_ss1      num_side_ss2      num_side_ss3      num_side_ss4      num_side_ss5      num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4       num_nod_ns5       num_elem_var      num_info           api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         phy.densityvelocity_3eqn_out.e     maximum_name_length                 %   
time_whole                            g4   	eb_status                             
   eb_prop1               name      ID              
   	ns_status         	                    
    ns_prop1      	         name      ID              
4   	ss_status         
                    
H   ss_prop1      
         name      ID              
\   coordx                      X      
p   coordy                      X      
�   coordz                      X          eb_names                       $      x   ns_names      	                 �      �   ss_names      
                 �      D   
coor_names                         d      �   node_num_map                    ,      P   connect1                  	elem_type         EDGE2         P      |   elem_num_map                    (      �   elem_ss1                          �   side_ss1                          �   elem_ss2                    P      �   side_ss2                    P      L   elem_ss3                          �   side_ss3                          �   elem_ss4                          �   side_ss4                          �   elem_ss5                          �   side_ss5                          �   node_ns1                    ,      �   node_ns2                          �   node_ns3                          �   node_ns4                          �   node_ns5                          �   name_elem_var                          D      �   vals_elem_var1eb1                          P      g<   vals_elem_var2eb1                          P      g�   elem_var_tab                             4   info_records                      W�      <                                                                             ?�������?ə�����?�333334?ٙ�����?�      ?�333333?�ffffff?陙����?�������?�                                                                                                      <\=	�S�r<l=	�S�r<u-�p~��<|=	�S�r<��&3\<�-�p~��<��h��M�<�=	�S�q<�ī(�??<��&3\pipe                                pipe                                                                                               inlet                            outlet                              pipe:out                         pipe                             outlet                           pipe:in                          inlet                                                                                                                                                              	   
                                                   	   	   
   
                              	   
   
                                                      	   	   
   
                                                               
                                          	   
               rho                              vel                                      ####################?��5�M8?��`�S?��#�z�	?��'���?��+�x�}?��0�=�?��4:}M*?��8f# Created by MOOSE #                                                             ####################                                                             ### Command Line Arguments ###                                                    /Users/andrsd/workspace/thm/thm-opt -i phy.densityvelocity_3eqn.i --error --... error-unused --error-override --no-gdb-backtrace### Version Info ###                                                                                              Framework Information:                                                           MOOSE Version:           git commit ed0fae0285 on 2021-08-18                     LibMesh Version:         ffab5c914090ad625645faa1bb4251d6b46f1c26                PETSc Version:           3.14.2                                                  Current Time:            Wed Aug 18 18:14:37 2021                                Executable Timestamp:    Wed Aug 18 18:08:08 2021                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 inactive                       = (no_default)                                    initial_from_file_timestep     = LATEST                                          initial_from_file_var          = INVALID                                         custom_blocks                  = (no_default)                                    custom_orders                  = (no_default)                                    element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [Components]                                                                       inactive                       = (no_default)                                                                                                                     [./inlet]                                                                          inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = InletDensityVelocity1Phase                        control_tags                 = Components                                        enable                       = 1                                                 input                        = pipe:in                                           reversible                   = 1                                                 rho                          = 805                                               vel                          = 1                                               [../]                                                                                                                                                             [./outlet]                                                                         inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = Outlet1Phase                                      control_tags                 = Components                                        enable                       = 1                                                 input                        = pipe:out                                          p                            = 7e+06                                             reversible                   = 0                                               [../]                                                                                                                                                             [./pipe]                                                                           inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = FlowChannel1Phase                                 A                            = 3.1415926536e-06                                  D_h                          = 2.0000000000e-03                                  PoD                          = 1                                                 axial_region_names           = INVALID                                           closures                     = simple                                            control_tags                 = Components                                        enable                       = 1                                                 f                            = 0.1                                               fp                           = fp                                                gravity_vector               = '(x,y,z)=(       0,        0,        0)'          heat_transfer_geom           = PIPE                                              initial_T                    = 510                                               initial_p                    = 7e6                                               initial_vel                  = 0                                                 length                       = 1                                                 lump_mass_matrix             = 0                                                 n_elems                      = 10                                                orientation                  = '(x,y,z)=(       1,        0,        0)'          pipe_pars_transferred        = 0                                                 position                     = '(x,y,z)=(       0,        0,        0)'          rdg_slope_reconstruction     = NONE                                              rotation                     = 0                                                 roughness                    = 0                                               [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      auto_preconditioning           = 1                                               inactive                       = (no_default)                                    isObjectAction                 = 1                                               type                           = Transient                                       abort_on_solve_fail            = 1                                               accept_on_max_fixed_point_iteration = 0                                          accept_on_max_picard_iteration = 0                                               auto_advance                   = INVALID                                         automatic_scaling              = INVALID                                         compute_initial_residual_before_preset_bcs = 0                                   compute_scaling_once           = 1                                               contact_line_search_allowed_lambda_cuts = 2                                      contact_line_search_ltol       = INVALID                                         control_tags                   = (no_default)                                    custom_abs_tol                 = 1e-50                                           custom_pp                      = INVALID                                         custom_rel_tol                 = 1e-08                                           direct_pp_value                = 0                                               disable_fixed_point_residual_norm_check = 0                                      disable_picard_residual_norm_check = 0                                           dt                             = 0.1                                             dtmax                          = 1e+30                                           dtmin                          = 2e-14                                           enable                         = 1                                               end_time                       = 1e+30                                           error_on_dtmin                 = 1                                               fixed_point_abs_tol            = 1e-50                                           fixed_point_algorithm          = picard                                          fixed_point_force_norms        = 0                                               fixed_point_max_its            = 1                                               fixed_point_min_its            = 1                                               fixed_point_rel_tol            = 1e-08                                           l_abs_tol                      = 1e-50                                           l_max_its                      = 100                                             l_tol                          = 0.001                                           line_search                    = default                                         line_search_package            = petsc                                           max_xfem_update                = 4294967295                                      mffd_type                      = wp                                              n_max_nonlinear_pingpong       = 100                                             n_startup_steps                = 0                                               nl_abs_div_tol                 = 1e+50                                           nl_abs_step_tol                = 0                                               nl_abs_tol                     = 1e-07                                           nl_div_tol                     = 1e+10                                           nl_forced_its                  = 0                                               nl_max_funcs                   = 10000                                           nl_max_its                     = 5                                               nl_rel_step_tol                = 0                                               nl_rel_tol                     = 1e-06                                           normalize_solution_diff_norm_by_dt = 1                                           num_grids                      = 1                                               num_steps                      = 50                                              off_diagonals_in_auto_scaling  = 0                                               outputs                        = INVALID                                         petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         picard_abs_tol                 = 1e-50                                           picard_custom_pp               = INVALID                                         picard_force_norms             = 0                                               picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           relaxation_factor              = 1                                               relaxed_variables              = (no_default)                                    reset_dt                       = 0                                               resid_vs_jac_scaling_param     = 0                                               restart_file_base              = (no_default)                                    scaling_group_variables        = INVALID                                         scheme                         = bdf2                                            skip_exception_check           = 0                                               snesmf_reuse_base              = 1                                               solve_type                     = NEWTON                                          splitting                      = INVALID                                         ss_check_tol                   = 1e-08                                           ss_tmin                        = 0                                               start_time                     = 0                                               steady_state_detection         = 0                                               steady_state_start_time        = 0                                               steady_state_tolerance         = 1e-08                                           time_period_ends               = INVALID                                         time_period_starts             = INVALID                                         time_periods                   = INVALID                                         timestep_tolerance             = 2e-14                                           trans_ss_check                 = 0                                               transformed_postprocessors     = (no_default)                                    transformed_variables          = (no_default)                                    update_xfem_at_timestep_begin  = 0                                               use_multiapp_dt                = 0                                               verbose                        = 0                                             []                                                                                                                                                                [FluidProperties]                                                                                                                                                   [./fp]                                                                             inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = StiffenedGasFluidProperties                       M                            = 0                                                 T_c                          = 0                                                 allow_duplicate_execution_on_initial = 0                                         allow_imperfect_jacobians    = 0                                                 allow_nonphysical_states     = 1                                                 control_tags                 = FluidProperties                                   cv                           = 1816                                              e_c                          = 0                                                 emit_on_nan                  = none                                              enable                       = 1                                                 execute_on                   = TIMESTEP_END                                      force_postaux                = 0                                                 force_preaux                 = 0                                                 force_preic                  = 0                                                 fp_type                      = single-phase-fp                                   gamma                        = 2.35                                              k                            = 0.5                                               mu                           = 0.0002818                                         p_inf                        = 1e+09                                             prop_getter_suffix           = (no_default)                                      q                            = -1.167e+06                                        q_prime                      = 0                                                 rho_c                        = 0                                                 use_displaced_mesh           = 0                                               [../]                                                                          []                                                                                                                                                                [GlobalParams]                                                                     closures                       = simple                                          gravity_vector                 = '(x,y,z)=(       0,        0,        0)'        initial_T                      = 510                                             initial_p                      = 7e6                                             initial_vel                    = 0                                             []                                                                                                                                                                [Outputs]                                                                          inactive                       = (no_default)                                    velocity_as_vector             = 0                                               append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = FINAL                                           exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         interval                       = 1                                               json                           = 0                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         perf_graph                     = 0                                               print_linear_converged_reason  = 1                                               print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_nonlinear_converged_reason = 1                                             print_perf_log                 = 0                                               show                           = 'rho vel'                                       solution_history               = 0                                               sync_times                     = (no_default)                                    tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                               xml                            = 0                                             []                                                                                                                                                                [Preconditioning]                                                                                                                                                   [./SMP_PJFNK]                                                                      inactive                     = (no_default)                                      isObjectAction               = 1                                                 type                         = SMP                                               control_tags                 = Preconditioning                                   coupled_groups               = INVALID                                           enable                       = 1                                                 full                         = 1                                                 ksp_norm                     = unpreconditioned                                  mffd_type                    = wp                                                off_diag_column              = INVALID                                           off_diag_row                 = INVALID                                           pc_side                      = default                                           petsc_options                = INVALID                                           petsc_options_iname          = INVALID                                           petsc_options_value          = INVALID                                           solve_type                   = INVALID                                           trust_my_coupling            = 0                                               [../]                                                                          []                                                                                 @������@�'����@�'���%>@�'����@�'�A�A4@�'���*�@�'��˪�@�'�f��T@�'��y�@�'�ԻD�@�'����q?��5�M8?��`�S?��#�z�	?��'���?��+�x�}?��0�=�?��4:}M*?��8f�L?��<��Q<?��@�FG