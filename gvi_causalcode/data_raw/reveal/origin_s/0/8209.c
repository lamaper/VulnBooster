void slurmctld_req ( slurm_msg_t * msg , connection_arg_t * arg ) {
 DEF_TIMERS ;
 int i , rpc_type_index = - 1 , rpc_user_index = - 1 ;
 uint32_t rpc_uid ;
 if ( arg && ( arg -> newsockfd >= 0 ) ) fd_set_nonblocking ( arg -> newsockfd ) ;


 if ( g_slurm_auth_errno ( msg -> auth_cred ) != SLURM_SUCCESS ) {
 error ( "Bad authentication: %s" , g_slurm_auth_errstr ( g_slurm_auth_errno ( msg -> auth_cred ) ) ) ;
 return ;
 }
 slurm_mutex_lock ( & rpc_mutex ) ;
 if ( rpc_type_size == 0 ) {
 rpc_type_size = 100 ;
 rpc_type_id = xmalloc ( sizeof ( uint16_t ) * rpc_type_size ) ;
 rpc_type_cnt = xmalloc ( sizeof ( uint32_t ) * rpc_type_size ) ;
 rpc_type_time = xmalloc ( sizeof ( uint64_t ) * rpc_type_size ) ;
 }
 for ( i = 0 ;
 i < rpc_type_size ;
 i ++ ) {
 if ( rpc_type_id [ i ] == 0 ) rpc_type_id [ i ] = msg -> msg_type ;
 else if ( rpc_type_id [ i ] != msg -> msg_type ) continue ;
 rpc_type_index = i ;
 break ;
 }
 if ( rpc_user_size == 0 ) {
 rpc_user_size = 200 ;
 rpc_user_id = xmalloc ( sizeof ( uint32_t ) * rpc_user_size ) ;
 rpc_user_cnt = xmalloc ( sizeof ( uint32_t ) * rpc_user_size ) ;
 rpc_user_time = xmalloc ( sizeof ( uint64_t ) * rpc_user_size ) ;
 }
 for ( i = 0 ;
 i < rpc_user_size ;
 i ++ ) {
 if ( ( rpc_user_id [ i ] == 0 ) && ( i != 0 ) ) rpc_user_id [ i ] = rpc_uid ;
 else if ( rpc_user_id [ i ] != rpc_uid ) continue ;
 rpc_user_index = i ;
 break ;
 }
 slurm_mutex_unlock ( & rpc_mutex ) ;
 START_TIMER ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_PROTOCOL ) {
 char * p = rpc_num2string ( msg -> msg_type ) ;
 if ( msg -> conn ) {
 info ( "%s: received opcode %s from persist conn on (%s)%s" , __func__ , p , msg -> conn -> cluster_name , msg -> conn -> rem_host ) ;
 }
 else if ( arg ) {
 char inetbuf [ 64 ] ;
 slurm_print_slurm_addr ( & arg -> cli_addr , inetbuf , sizeof ( inetbuf ) ) ;
 info ( "%s: received opcode %s from %s" , __func__ , p , inetbuf ) ;
 }
 else {
 error ( "%s: No arg given and this doesn't appear to be a persistent connection, this should never happen" , __func__ ) ;
 }
 }
 switch ( msg -> msg_type ) {
 case REQUEST_RESOURCE_ALLOCATION : _slurm_rpc_allocate_resources ( msg ) ;
 break ;
 case REQUEST_JOB_PACK_ALLOCATION : _slurm_rpc_allocate_pack ( msg ) ;
 break ;
 case REQUEST_BUILD_INFO : _slurm_rpc_dump_conf ( msg ) ;
 break ;
 case REQUEST_JOB_INFO : _slurm_rpc_dump_jobs ( msg ) ;
 break ;
 case REQUEST_JOB_USER_INFO : _slurm_rpc_dump_jobs_user ( msg ) ;
 break ;
 case REQUEST_JOB_INFO_SINGLE : _slurm_rpc_dump_job_single ( msg ) ;
 break ;
 case REQUEST_BATCH_SCRIPT : _slurm_rpc_dump_batch_script ( msg ) ;
 break ;
 case REQUEST_SHARE_INFO : _slurm_rpc_get_shares ( msg ) ;
 break ;
 case REQUEST_PRIORITY_FACTORS : _slurm_rpc_get_priority_factors ( msg ) ;
 break ;
 case REQUEST_JOB_END_TIME : _slurm_rpc_end_time ( msg ) ;
 break ;
 case REQUEST_FED_INFO : _slurm_rpc_get_fed ( msg ) ;
 break ;
 case REQUEST_FRONT_END_INFO : _slurm_rpc_dump_front_end ( msg ) ;
 break ;
 case REQUEST_NODE_INFO : _slurm_rpc_dump_nodes ( msg ) ;
 break ;
 case REQUEST_NODE_INFO_SINGLE : _slurm_rpc_dump_node_single ( msg ) ;
 break ;
 case REQUEST_PARTITION_INFO : _slurm_rpc_dump_partitions ( msg ) ;
 break ;
 case MESSAGE_EPILOG_COMPLETE : i = 0 ;
 _slurm_rpc_epilog_complete ( msg , ( bool * ) & i , 0 ) ;
 break ;
 case REQUEST_CANCEL_JOB_STEP : _slurm_rpc_job_step_kill ( rpc_uid , msg ) ;
 break ;
 case REQUEST_COMPLETE_JOB_ALLOCATION : _slurm_rpc_complete_job_allocation ( msg ) ;
 break ;
 case REQUEST_COMPLETE_PROLOG : _slurm_rpc_complete_prolog ( msg ) ;
 break ;
 case REQUEST_COMPLETE_BATCH_JOB : case REQUEST_COMPLETE_BATCH_SCRIPT : i = 0 ;
 _slurm_rpc_complete_batch_script ( msg , ( bool * ) & i , 0 ) ;
 break ;
 case REQUEST_JOB_STEP_CREATE : _slurm_rpc_job_step_create ( msg ) ;
 break ;
 case REQUEST_JOB_STEP_INFO : _slurm_rpc_job_step_get_info ( msg ) ;
 break ;
 case REQUEST_JOB_WILL_RUN : _slurm_rpc_job_will_run ( msg ) ;
 break ;
 case REQUEST_SIB_JOB_LOCK : _slurm_rpc_sib_job_lock ( rpc_uid , msg ) ;
 break ;
 case REQUEST_SIB_JOB_UNLOCK : _slurm_rpc_sib_job_unlock ( rpc_uid , msg ) ;
 break ;
 case REQUEST_CTLD_MULT_MSG : _proc_multi_msg ( rpc_uid , msg ) ;
 break ;
 case MESSAGE_NODE_REGISTRATION_STATUS : _slurm_rpc_node_registration ( msg , 0 ) ;
 break ;
 case REQUEST_JOB_ALLOCATION_INFO : case DEFUNCT_REQUEST_JOB_ALLOCATION_INFO_LITE : _slurm_rpc_job_alloc_info ( msg ) ;
 break ;
 case REQUEST_JOB_PACK_ALLOC_INFO : _slurm_rpc_job_pack_alloc_info ( msg ) ;
 break ;
 case REQUEST_JOB_SBCAST_CRED : _slurm_rpc_job_sbcast_cred ( msg ) ;
 break ;
 case REQUEST_PING : _slurm_rpc_ping ( msg ) ;
 break ;
 case REQUEST_RECONFIGURE : _slurm_rpc_reconfigure_controller ( msg ) ;
 break ;
 case REQUEST_CONTROL : _slurm_rpc_shutdown_controller ( msg ) ;
 break ;
 case REQUEST_TAKEOVER : _slurm_rpc_takeover ( msg ) ;
 break ;
 case REQUEST_SHUTDOWN : _slurm_rpc_shutdown_controller ( msg ) ;
 break ;
 case REQUEST_SHUTDOWN_IMMEDIATE : _slurm_rpc_shutdown_controller_immediate ( msg ) ;
 break ;
 case REQUEST_SUBMIT_BATCH_JOB : _slurm_rpc_submit_batch_job ( msg ) ;
 break ;
 case REQUEST_SUBMIT_BATCH_JOB_PACK : _slurm_rpc_submit_batch_pack_job ( msg ) ;
 break ;
 case REQUEST_UPDATE_FRONT_END : _slurm_rpc_update_front_end ( msg ) ;
 break ;
 case REQUEST_UPDATE_JOB : _slurm_rpc_update_job ( msg ) ;
 break ;
 case REQUEST_UPDATE_NODE : _slurm_rpc_update_node ( msg ) ;
 break ;
 case REQUEST_UPDATE_LAYOUT : _slurm_rpc_update_layout ( msg ) ;
 break ;
 case REQUEST_CREATE_PARTITION : case REQUEST_UPDATE_PARTITION : _slurm_rpc_update_partition ( msg ) ;
 break ;
 case REQUEST_UPDATE_POWERCAP : _slurm_rpc_update_powercap ( msg ) ;
 break ;
 case REQUEST_DELETE_PARTITION : _slurm_rpc_delete_partition ( msg ) ;
 break ;
 case REQUEST_CREATE_RESERVATION : _slurm_rpc_resv_create ( msg ) ;
 break ;
 case REQUEST_UPDATE_RESERVATION : _slurm_rpc_resv_update ( msg ) ;
 break ;
 case REQUEST_DELETE_RESERVATION : _slurm_rpc_resv_delete ( msg ) ;
 break ;
 case REQUEST_UPDATE_BLOCK : _slurm_rpc_update_block ( msg ) ;
 break ;
 case REQUEST_RESERVATION_INFO : _slurm_rpc_resv_show ( msg ) ;
 break ;
 case REQUEST_LAYOUT_INFO : _slurm_rpc_layout_show ( msg ) ;
 break ;
 case REQUEST_NODE_REGISTRATION_STATUS : error ( "slurmctld is talking with itself. " "SlurmctldPort == SlurmdPort" ) ;
 slurm_send_rc_msg ( msg , EINVAL ) ;
 break ;
 case REQUEST_CHECKPOINT : _slurm_rpc_checkpoint ( msg ) ;
 break ;
 case REQUEST_CHECKPOINT_COMP : _slurm_rpc_checkpoint_comp ( msg ) ;
 break ;
 case REQUEST_CHECKPOINT_TASK_COMP : _slurm_rpc_checkpoint_task_comp ( msg ) ;
 break ;
 case REQUEST_SUSPEND : _slurm_rpc_suspend ( msg ) ;
 break ;
 case REQUEST_TOP_JOB : _slurm_rpc_top_job ( msg ) ;
 break ;
 case REQUEST_JOB_REQUEUE : _slurm_rpc_requeue ( msg ) ;
 break ;
 case REQUEST_JOB_READY : _slurm_rpc_job_ready ( msg ) ;
 break ;
 case REQUEST_BLOCK_INFO : _slurm_rpc_block_info ( msg ) ;
 break ;
 case REQUEST_BURST_BUFFER_INFO : _slurm_rpc_burst_buffer_info ( msg ) ;
 break ;
 case REQUEST_STEP_COMPLETE : _slurm_rpc_step_complete ( msg , 0 ) ;
 break ;
 case REQUEST_STEP_LAYOUT : _slurm_rpc_step_layout ( msg ) ;
 break ;
 case REQUEST_UPDATE_JOB_STEP : _slurm_rpc_step_update ( msg ) ;
 break ;
 case REQUEST_TRIGGER_SET : _slurm_rpc_trigger_set ( msg ) ;
 break ;
 case REQUEST_TRIGGER_GET : _slurm_rpc_trigger_get ( msg ) ;
 break ;
 case REQUEST_TRIGGER_CLEAR : _slurm_rpc_trigger_clear ( msg ) ;
 break ;
 case REQUEST_TRIGGER_PULL : _slurm_rpc_trigger_pull ( msg ) ;
 break ;
 case REQUEST_JOB_NOTIFY : _slurm_rpc_job_notify ( msg ) ;
 break ;
 case REQUEST_SET_DEBUG_FLAGS : _slurm_rpc_set_debug_flags ( msg ) ;
 break ;
 case REQUEST_SET_DEBUG_LEVEL : _slurm_rpc_set_debug_level ( msg ) ;
 break ;
 case REQUEST_SET_SCHEDLOG_LEVEL : _slurm_rpc_set_schedlog_level ( msg ) ;
 break ;
 case ACCOUNTING_UPDATE_MSG : _slurm_rpc_accounting_update_msg ( msg ) ;
 break ;
 case ACCOUNTING_FIRST_REG : _slurm_rpc_accounting_first_reg ( msg ) ;
 break ;
 case ACCOUNTING_REGISTER_CTLD : _slurm_rpc_accounting_register_ctld ( msg ) ;
 break ;
 case REQUEST_TOPO_INFO : _slurm_rpc_get_topo ( msg ) ;
 break ;
 case REQUEST_POWERCAP_INFO : _slurm_rpc_get_powercap ( msg ) ;
 break ;
 case REQUEST_SPANK_ENVIRONMENT : _slurm_rpc_dump_spank ( msg ) ;
 break ;
 case REQUEST_REBOOT_NODES : _slurm_rpc_reboot_nodes ( msg ) ;
 break ;
 case REQUEST_STATS_INFO : _slurm_rpc_dump_stats ( msg ) ;
 break ;
 case REQUEST_LICENSE_INFO : _slurm_rpc_dump_licenses ( msg ) ;
 break ;
 case REQUEST_KILL_JOB : _slurm_rpc_kill_job ( msg ) ;
 break ;
 case MESSAGE_COMPOSITE : _slurm_rpc_composite_msg ( msg ) ;
 break ;
 case REQUEST_ASSOC_MGR_INFO : _slurm_rpc_assoc_mgr_info ( msg ) ;
 break ;
 case REQUEST_PERSIST_INIT : if ( msg -> conn ) error ( "We already have a persistent connect, this should never happen" ) ;
 _slurm_rpc_persist_init ( msg , arg ) ;
 break ;
 case REQUEST_EVENT_LOG : _slurm_rpc_event_log ( msg ) ;
 break ;
 case REQUEST_SET_FS_DAMPENING_FACTOR : _slurm_rpc_set_fs_dampening_factor ( msg ) ;
 break ;
 default : error ( "invalid RPC msg_type=%u" , msg -> msg_type ) ;
 slurm_send_rc_msg ( msg , EINVAL ) ;
 break ;
 }
 END_TIMER ;
 slurm_mutex_lock ( & rpc_mutex ) ;
 if ( rpc_type_index >= 0 ) {
 rpc_type_cnt [ rpc_type_index ] ++ ;
 rpc_type_time [ rpc_type_index ] += DELTA_TIMER ;
 }
 if ( rpc_user_index >= 0 ) {
 rpc_user_cnt [ rpc_user_index ] ++ ;
 rpc_user_time [ rpc_user_index ] += DELTA_TIMER ;
 }
 slurm_mutex_unlock ( & rpc_mutex ) ;
 }