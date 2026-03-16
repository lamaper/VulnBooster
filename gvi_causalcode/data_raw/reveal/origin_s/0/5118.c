inline static void _slurm_rpc_trigger_get ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 trigger_info_msg_t * resp_data ;
 trigger_info_msg_t * trigger_ptr = ( trigger_info_msg_t * ) msg -> data ;
 slurm_msg_t response_msg ;
 DEF_TIMERS ;
 START_TIMER ;
 debug ( "Processing RPC: REQUEST_TRIGGER_GET from uid=%d" , uid ) ;
 resp_data = trigger_get ( uid , trigger_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_trigger_get" ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_TRIGGER_GET ;
 response_msg . data = resp_data ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 slurm_free_trigger_msg ( resp_data ) ;
 }