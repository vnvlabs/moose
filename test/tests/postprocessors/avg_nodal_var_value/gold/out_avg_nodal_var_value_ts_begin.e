CDF   
   
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes         num_elem      
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1        num_nod_per_el1    	   num_side_ss1      
num_df_ss1        num_side_ss2      
num_df_ss2        num_side_ss3      
num_df_ss3        num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4       num_nod_ns5       num_nod_ns6       num_nod_ns7       num_nod_var       num_info   �   num_glo_var             api_version       @��H   version       @��H   floating_point_word_size            	file_size               title         "out_avg_nodal_var_value_ts_begin.e     maximum_name_length                 %   
time_whole                        [�   	eb_status                         	�   eb_prop1               name      ID          	�   	ns_status         	                	�   ns_prop1      	         name      ID          	�   	ss_status         
                
   ss_prop1      
         name      ID          
   coordx                      �  
$   coordy                      �  
�   eb_names                       $  �   ns_names      	                 �  �   ss_names      
                 d  �   
coor_names                         D  $   connect1                  	elem_type         QUAD9         �  h   elem_num_map                      �   elem_ss1                          side_ss1                       (   dist_fact_ss1                          H   elem_ss2                      h   side_ss2                      p   dist_fact_ss2                          x   elem_ss3                      �   side_ss3                      �   dist_fact_ss3                          �   node_ns1                    @  �   node_ns2                         node_ns3                         node_ns4                          node_ns5                      $   node_ns6                      8   node_ns7                      <   vals_nod_var1                          �  [�   vals_nod_var2                          �  \X   name_nod_var                       D  @   info_records                      K�  �   name_glo_var                       d  [$   vals_glo_var                         ]                                                 
                  ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                      ?�              ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                      ?�              ?�      ?�              ?�              ?�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     	      
                                                                                                                                                                                                                                                                                 
                                                      
                  u                                v                                  ####################?�������?������?�������?�������?�������?٤                  # Created by MOOSE #�ffffa�?�������?�������?������?�������                      ####################[K��"�?~����Z�                                               ### Command Line Arguments ###                                                   -iQm/��?�Qm/��                                                                 avg_nodal_var_value_ts_begin.i                                                                                                                                    ### Input File ###                                                                                                                                                                                                                                 [Mesh]                                                                             second_order                   = 0                                               file                           = square-2x2-nodeids.e                            nemesis                        = 0                                               patch_size                     = 40                                              skip_partitioning              = 0                                               uniform_refine                 = 0                                             []                                                                                                                                                                [Functions]                                                                        [./force_fn]                                                                       type                         = ParsedFunction                                    execute_on                   = residual                                          vals                         =                                                   value                        = 1-x*x+2*t                                         vars                         =                                                 [../]                                                                                                                                                             [./exact_fn]                                                                       type                         = ParsedFunction                                    execute_on                   = residual                                          vals                         =                                                   value                        = (1-x*x)*t                                         vars                         =                                                 [../]                                                                                                                                                             [./left_bc]                                                                        type                         = ParsedFunction                                    execute_on                   = residual                                          vals                         =                                                   value                        = t                                                 vars                         =                                                 [../]                                                                          []                                                                                                                                                                [Variables]                                                                        [./v]                                                                              initial_from_file_timestep   = 2                                               [../]                                                                                                                                                             [./u]                                                                              initial_from_file_timestep   = 2                                               [../]                                                                                                                                                             [./v]                                                                              family                       = LAGRANGE                                          initial_condition            = 0                                                 order                        = SECOND                                            scaling                      = 1                                               [../]                                                                                                                                                             [./u]                                                                              family                       = LAGRANGE                                          initial_condition            = 0                                                 order                        = SECOND                                            scaling                      = 1                                               [../]                                                                          []                                                                                                                                                                [Kernels]                                                                          [./time_u]                                                                         type                         = TimeDerivative                                    execute_on                   = residual                                          start_time                   = -1.79769e+308                                     stop_time                    = 1.79769e+308                                      variable                     = u                                               [../]                                                                                                                                                             [./diff_u]                                                                         type                         = Diffusion                                         execute_on                   = residual                                          start_time                   = -1.79769e+308                                     stop_time                    = 1.79769e+308                                      variable                     = u                                               [../]                                                                                                                                                             [./ffn_u]                                                                          type                         = UserForcingFunction                               execute_on                   = residual                                          function                     = force_fn                                          start_time                   = -1.79769e+308                                     stop_time                    = 1.79769e+308                                      variable                     = u                                               [../]                                                                                                                                                             [./time_v]                                                                         type                         = TimeDerivative                                    execute_on                   = residual                                          start_time                   = -1.79769e+308                                     stop_time                    = 1.79769e+308                                      variable                     = v                                               [../]                                                                                                                                                             [./diff_v]                                                                         type                         = Diffusion                                         execute_on                   = residual                                          start_time                   = -1.79769e+308                                     stop_time                    = 1.79769e+308                                      variable                     = v                                               [../]                                                                          []                                                                                                                                                                [BCs]                                                                              [./right_v]                                                                        type                         = DirichletBC                                       boundary                     = 2                                                 execute_on                   = residual                                          value                        = 0                                                 variable                     = v                                               [../]                                                                                                                                                             [./left_v]                                                                         type                         = FunctionDirichletBC                               boundary                     = 3                                                 execute_on                   = residual                                          function                     = left_bc                                           variable                     = v                                               [../]                                                                                                                                                             [./all_u]                                                                          type                         = FunctionDirichletBC                               boundary                     = 1                                                 execute_on                   = residual                                          function                     = exact_fn                                          variable                     = u                                               [../]                                                                          []                                                                                                                                                                [Postprocessors]                                                                   [./node4]                                                                          type                         = AverageNodalVariableValue                         execute_on                   = residual                                          nodeset                      = 13                                                output                       = 1                                                 variable                     = v                                               [../]                                                                                                                                                             [./node1]                                                                          type                         = AverageNodalVariableValue                         execute_on                   = TIMESTEP_BEGIN                                    nodeset                      = 10                                                output                       = 1                                                 variable                     = u                                               [../]                                                                                                                                                             [./l2]                                                                             type                         = ElementL2Error                                    block                        = 65535                                             execute_on                   = residual                                          function                     = exact_fn                                          output                       = 1                                                 variable                     = u                                               [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-05                                           nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-50                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-08                                           no_fe_reinit                   = 0                                               petsc_options                  = -snes_mf_operator                               scheme                         = backward-euler                                  type                           = Transient                                       dt                             = 0.1                                             dtmax                          = 1e+30                                           dtmin                          = 0                                               end_time                       = 1                                               execute_on                     = residual                                        growth_factor                  = 2                                               n_startup_steps                = 0                                               num_steps                      = 1.79769e+308                                    ss_check_tol                   = 1e-08                                           ss_tmin                        = 0                                               start_time                     = 0                                               sync_times                     = -1                                              trans_ss_check                 = 0                                             []                                                                                                                                                                [Output]                                                                           exodus                         = 1                                               file_base                      = out_avg_nodal_var_value_ts_begin                gmv                            = 0                                               gnuplot_format                 = ps                                              interval                       = 1                                               iteration_plot_start_time      = 1.79769e+308                                    nemesis                        = 0                                               output_displaced               = 0                                               output_initial                 = 0                                               perf_log                       = 1                                               postprocessor_csv              = 0                                               postprocessor_ensight          = 0                                               postprocessor_gnuplot          = 0                                               postprocessor_screen           = 1                                               print_linear_residuals         = 0                                               screen_interval                = 1                                               show_setup_log_early           = 0                                               tecplot                        = 0                                               tecplot_binary                 = 0                                               xda                            = 0                                             []                                                                                                                                                                [check_integrity]                                                                []                                                                                                                                                                [copy_nodal_vars]                                                                  initial_from_file_timestep     = 2                                             []                                                                                                                                                                [init_problem]                                                                   []                                                                                                                                                                [no_action]                                                                      []                                                                                                                                                                [setup_dampers]                                                                  []                                                                                                                                                                [setup_quadrature]                                                                 order                          = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [no_action]                                                                       l2                               node1                            node4                             ?�������        ?�33331�?�3333/�        ?�ffffd�?�3333*�?�ffffff        ?�ffffe8?�������?�������?������?�������?������?�������?�33331�        ?�33330?�ffffd�        ?�ffffa�?�������?�������?������?�������        ?�[K��(�?�[K��6f        ?~����+�?�[K��"�?~����Z�        ?~����#�?�������?�������?�Qm/e�?�������?�Qm/s?�Qm/t??�[K��@k        ?�[K��:?~������        ?~����\?�������?�������?�Qm/��?�Qm/��=!`�v̹        ?�������?ə�����        ?�33332�?�33330�        ?�ffffe�?�3333.F?�ffffe�        ?�ffffe�?ə����	?ə����	?������p?ə����	?�������?������(?�33332�        ?�33331_?�ffffe�        ?�ffffcU?ə����	?ə����	?������p?�������        ?��
(�/u?��
(�8        ?���Ω&?��
(�,#?���Ω34        ?���Ω$;?ə����	?ə����	?�oI��5U?ə����	?�oI��<?�oI��<�?��
(�>'        ?��
(�;�?���ΩS�        ?���Ω>�?ə����	?ə����	?�oI��Ch?�oI��B�=ܰ�(j?�33331�?ə����	?�333333        ?������a?������         ?�����̅?�����ǘ?������a        ?������?�33332�?�33332�?�������?�33332�?������?������p?������a        ?������h?�����̅        ?������@?�33332�?�33332�?�������?�������        ?�~�,77�?�~�,7><        ?�Tt�@�?�~�,76�?�Tt�@�        ?�Tt�@*?�33332�?�33332�?ƌh����?�33332�?ƌh����?ƌh���|?�~�,7E0        ?�~�,7A?�Tt�@,�        ?�Tt�@?�33332�?�33332�?ƌh����?ƌh����=��y�2l?�33332�?�33332�?ٙ�����        ?�33333?�33331�        ?�fffffB?�33330u?�ffffe�        ?�ffffe�?ٙ����d?ٙ����d?�������?ٙ����d?�������?������L?�33333        ?�33331�?�fffffB        ?�ffffd�?ٙ����d?ٙ����d?�������?�������        ?� �la�?� �lf        ?�V��vg?� �la�?�V��}        ?�V��vJ?ٙ����d?ٙ����d?���1�?ٙ����d?���1�?���1��?� �lkp        ?� �lh3?�V����        ?�V����?ٙ����d?ٙ����d?���1��?���1�=�E��F[?������a?ٙ����d?�              ?�������?������b        ?�������?������/?������(        ?������?�������?�������?�������?�������?�������?������(?�������        ?������t?�������        ?������t?�������?�������?�������?�������        ?�Cl��y�?�Cl��        ?�_%N��?�Cl��z ?�_%N�
�        ?�_%N�?�������?�������?ԗ�LiE�?�������?ԗ�LiIS?ԗ�LiH�?�Cl����        ?�Cl����?�_%N�!E        ?�_%N�]?�������?�������?ԗ�LiN�?ԗ�LiM =�@�|B?�33333?�������?�333333        ?�����̩?������
        ?�����̻?�������?������a        ?������=?�33333?�33333?�������?�33333?�������?�������?�����̩        ?������.?�����̻        ?������?�33333?�33333?�������?������C        ?Έ5'���?Έ5'��I        ?��'�ʕ�?Έ5'���?��'�ʞ�        ?��'�ʖ?�33333?�33333?�X�c#��?�33333?�X�c#��?�X�c#��?Έ5'��v        ?Έ5'��=?��'�ʶ�        ?��'�ʪ?�33333?�33333?�X�c#�Q?�X�c#ĳ=�9�F?�������?�33333?�ffffff        ?�����̻?�������        ?ә�����?������\?ә����.        ?ә�����?�fffffK?�fffffK?�������?�fffffK?�������?�������?�����̻        ?�������?ә�����        ?ә�����?�fffffK?�fffffK?�������?������C        ?�n�.q�w?�n�.q�Z        ?�r`��pq?�n�.q��?�r`��u        ?�r`��p�?�fffffK?�fffffK?����r?�fffffK?����c?���沊?�n�.q�'        ?�n�.q��?�r`���x        ?�r`��z�?�fffffK?�fffffK?����(?���淉=M��C�?�����̩?�fffffK?陙����        ?�33333!?�33332R        ?�fffffT?�33331�?�ffffe�        ?�ffffe�?陙���?陙���?�������?陙���?�������?�������?�33333!        ?�33332[?�fffffT        ?�ffffe�?陙���?陙���?�������?������C        ?՝ً�$�?՝ً�'�        ?ğ�L�?՝ً�$�?ğ�L틨        ?ğ�L�'?陙���?陙���?�t����e?陙���?�t����g?�t�����?՝ً�+�        ?՝ً�)C?ğ�L�.        ?ğ�L푵?陙���?陙���?�t����R?�t�����=j�܆C?�����̻?陙���?�������        ?噙����?噙����        ?�33333!?噙���(?�33332�        ?�33332�?�����̲?�����̲?�������?�����̲?�������?�������?噙����        ?噙����?�33333!        ?�33332m?�����̲?�����̲?�������?������C        ?���M�R?���M�G        ?���ݕ��?���M��?���ݕ��        ?���ݕ�?�����̲?�����̲?��ZbI?�����̲?��ZbK?��ZbJ�?���M�8        ?���M��?���ݕ�J        ?���ݕ��?�����̲?�����̲?��ZbN?��ZbM2=�,�6z1?�33333!?�����̲?�              ?�������?������        ?�������?�������?�������        ?������^?�������?�������?�������?�������?�������?�������?�������        ?������(?�������        ?������:?�������?�������?�������?������:        ?��$�?��$ �        ?�����l?��$?����        ?������?�������?�������?�@`�d�?�������?�@`�f�?�@`�f?��$$�        ?��$"t?�����        ?����	?�������?�������?�@`�i�?�@`�h�=�a7��?噙����?�������