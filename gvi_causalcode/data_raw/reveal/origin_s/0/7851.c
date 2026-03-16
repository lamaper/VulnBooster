static void _slurm_rpc_persist_init ( slurm_msg_t * msg , connection_arg_t * arg ) {
 DEF_TIMERS ;
 int rc = SLURM_SUCCESS ;
 char * comment = NULL ;
 uint16_t port ;
 Buf ret_buf ;
 slurm_persist_conn_t * persist_conn = NULL , p_tmp ;
 persist_init_req_msg_t * persist_init = msg -> data ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 xassert ( arg ) ;
 START_TIMER ;
 if ( persist_init -> version > SLURM_PROTOCOL_VERSION ) persist_init -> version = SLURM_PROTOCOL_VERSION ;
 if ( ! validate_slurm_user ( uid ) ) {
 memset ( & p_tmp , 0 , sizeof ( slurm_persist_conn_t ) ) ;
 p_tmp . fd = arg -> newsockfd ;
 p_tmp . cluster_name = persist_init -> cluster_name ;
 p_tmp . version = persist_init -> version ;
 p_tmp . shutdown = & slurmctld_config . shutdown_time ;
 rc = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, REQUEST_PERSIST_INIT RPC " "from uid=%d" , uid ) ;
 goto end_it ;
 }
 persist_conn = xmalloc ( sizeof ( slurm_persist_conn_t ) ) ;
 persist_conn -> auth_cred = msg -> auth_cred ;
 msg -> auth_cred = NULL ;
 persist_conn -> cluster_name = persist_init -> cluster_name ;
 persist_init -> cluster_name = NULL ;
 persist_conn -> fd = arg -> newsockfd ;
 arg -> newsockfd = - 1 ;
 persist_conn -> callback_proc = _process_persist_conn ;
 persist_conn -> persist_type = persist_init -> persist_type ;
 persist_conn -> rem_port = persist_init -> port ;
 persist_conn -> rem_host = xmalloc_nz ( sizeof ( char ) * 16 ) ;
 slurm_get_ip_str ( & arg -> cli_addr , & port , persist_conn -> rem_host , sizeof ( char ) * 16 ) ;
 persist_conn -> shutdown = & slurmctld_config . shutdown_time ;
 persist_conn -> version = persist_init -> version ;
 memcpy ( & p_tmp , persist_conn , sizeof ( slurm_persist_conn_t ) ) ;
 if ( persist_init -> persist_type == PERSIST_TYPE_FED ) rc = fed_mgr_add_sibling_conn ( persist_conn , & comment ) ;
 else rc = SLURM_ERROR ;
 end_it : ret_buf = slurm_persist_make_rc_msg ( & p_tmp , rc , comment , p_tmp . version ) ;
 if ( slurm_persist_send_msg ( & p_tmp , ret_buf ) != SLURM_SUCCESS ) {
 debug ( "Problem sending response to connection %d uid(%d)" , p_tmp . fd , uid ) ;
 }
 if ( rc && persist_conn ) {
 persist_conn -> fd = - 1 ;
 slurm_persist_conn_destroy ( persist_conn ) ;
 }
 xfree ( comment ) ;
 free_buf ( ret_buf ) ;
 END_TIMER ;
 }