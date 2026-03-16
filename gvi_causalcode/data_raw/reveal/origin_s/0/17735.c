static void _slurm_rpc_get_shares ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 shares_request_msg_t * req_msg = ( shares_request_msg_t * ) msg -> data ;
 shares_response_msg_t resp_msg ;
 slurm_msg_t response_msg ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_SHARE_INFO from uid=%d" , uid ) ;
 memset ( & resp_msg , 0 , sizeof ( shares_response_msg_t ) ) ;
 assoc_mgr_get_shares ( acct_db_conn , uid , req_msg , & resp_msg ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_SHARE_INFO ;
 response_msg . data = & resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 FREE_NULL_LIST ( resp_msg . assoc_shares_list ) ;
 END_TIMER2 ( "_slurm_rpc_get_share" ) ;
 debug2 ( "_slurm_rpc_get_shares %s" , TIME_STR ) ;
 }