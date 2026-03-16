static void _slurm_rpc_get_priority_factors ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 priority_factors_request_msg_t * req_msg = ( priority_factors_request_msg_t * ) msg -> data ;
 priority_factors_response_msg_t resp_msg ;
 slurm_msg_t response_msg ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_PRIORITY_FACTORS from uid=%d" , uid ) ;
 resp_msg . priority_factors_list = priority_g_get_priority_factors_list ( req_msg , uid ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_PRIORITY_FACTORS ;
 response_msg . data = & resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 FREE_NULL_LIST ( resp_msg . priority_factors_list ) ;
 END_TIMER2 ( "_slurm_rpc_get_priority_factors" ) ;
 debug2 ( "_slurm_rpc_get_priority_factors %s" , TIME_STR ) ;
 }