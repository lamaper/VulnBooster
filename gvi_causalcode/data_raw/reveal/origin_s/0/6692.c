static void _slurm_rpc_assoc_mgr_info ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump = NULL ;
 int dump_size = 0 ;
 slurm_msg_t response_msg ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "%s: Processing RPC: REQUEST_ASSOC_MGR_INFO uid=%d" , __func__ , uid ) ;
 assoc_mgr_info_get_pack_msg ( & dump , & dump_size , ( assoc_mgr_info_request_msg_t * ) msg -> data , uid , acct_db_conn , msg -> protocol_version ) ;
 END_TIMER2 ( "_slurm_rpc_assoc_mgr_info" ) ;
 debug2 ( "%s: size=%d %s" , __func__ , dump_size , TIME_STR ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_ASSOC_MGR_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }