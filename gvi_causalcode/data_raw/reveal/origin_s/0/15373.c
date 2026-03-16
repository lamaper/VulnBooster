static void _build_alloc_msg ( struct job_record * job_ptr , resource_allocation_response_msg_t * alloc_msg , int error_code , char * job_submit_user_msg ) {
 int i ;
 memset ( alloc_msg , 0 , sizeof ( resource_allocation_response_msg_t ) ) ;
 if ( job_ptr -> job_resrcs && job_ptr -> job_resrcs -> cpu_array_cnt ) {
 alloc_msg -> num_cpu_groups = job_ptr -> job_resrcs -> cpu_array_cnt ;
 alloc_msg -> cpu_count_reps = xmalloc ( sizeof ( uint32_t ) * job_ptr -> job_resrcs -> cpu_array_cnt ) ;
 memcpy ( alloc_msg -> cpu_count_reps , job_ptr -> job_resrcs -> cpu_array_reps , ( sizeof ( uint32_t ) * job_ptr -> job_resrcs -> cpu_array_cnt ) ) ;
 alloc_msg -> cpus_per_node = xmalloc ( sizeof ( uint16_t ) * job_ptr -> job_resrcs -> cpu_array_cnt ) ;
 memcpy ( alloc_msg -> cpus_per_node , job_ptr -> job_resrcs -> cpu_array_value , ( sizeof ( uint16_t ) * job_ptr -> job_resrcs -> cpu_array_cnt ) ) ;
 }
 alloc_msg -> error_code = error_code ;
 alloc_msg -> job_submit_user_msg = xstrdup ( job_submit_user_msg ) ;
 alloc_msg -> job_id = job_ptr -> job_id ;
 alloc_msg -> node_cnt = job_ptr -> node_cnt ;
 alloc_msg -> node_list = xstrdup ( job_ptr -> nodes ) ;
 alloc_msg -> partition = xstrdup ( job_ptr -> partition ) ;
 alloc_msg -> alias_list = xstrdup ( job_ptr -> alias_list ) ;
 alloc_msg -> select_jobinfo = select_g_select_jobinfo_copy ( job_ptr -> select_jobinfo ) ;
 if ( job_ptr -> details ) {
 alloc_msg -> pn_min_memory = job_ptr -> details -> pn_min_memory ;
 if ( job_ptr -> details -> mc_ptr ) {
 alloc_msg -> ntasks_per_board = job_ptr -> details -> mc_ptr -> ntasks_per_board ;
 alloc_msg -> ntasks_per_core = job_ptr -> details -> mc_ptr -> ntasks_per_core ;
 alloc_msg -> ntasks_per_socket = job_ptr -> details -> mc_ptr -> ntasks_per_socket ;
 }
 if ( job_ptr -> details -> env_cnt ) {
 alloc_msg -> env_size = job_ptr -> details -> env_cnt ;
 alloc_msg -> environment = xmalloc ( sizeof ( char * ) * alloc_msg -> env_size ) ;
 for ( i = 0 ;
 i < alloc_msg -> env_size ;
 i ++ ) {
 alloc_msg -> environment [ i ] = xstrdup ( job_ptr -> details -> env_sup [ i ] ) ;
 }
 }
 }
 else {
 alloc_msg -> pn_min_memory = 0 ;
 alloc_msg -> ntasks_per_board = NO_VAL16 ;
 alloc_msg -> ntasks_per_core = NO_VAL16 ;
 alloc_msg -> ntasks_per_socket = NO_VAL16 ;
 }
 if ( job_ptr -> account ) alloc_msg -> account = xstrdup ( job_ptr -> account ) ;
 if ( job_ptr -> qos_ptr ) {
 slurmdb_qos_rec_t * qos ;
 qos = ( slurmdb_qos_rec_t * ) job_ptr -> qos_ptr ;
 alloc_msg -> qos = xstrdup ( qos -> name ) ;
 }
 if ( job_ptr -> resv_name ) alloc_msg -> resv_name = xstrdup ( job_ptr -> resv_name ) ;
 set_remote_working_response ( alloc_msg , job_ptr , job_ptr -> origin_cluster ) ;
 }