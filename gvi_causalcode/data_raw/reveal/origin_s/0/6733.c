static void _slurm_rpc_get_fed ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 slurm_msg_t response_msg ;
 slurmctld_lock_t fed_read_lock = {
 NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_FED_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( fed_read_lock ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_FED_INFO ;
 response_msg . data = fed_mgr_fed_rec ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 unlock_slurmctld ( fed_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_get_fed" ) ;
 debug2 ( "%s %s" , __func__ , TIME_STR ) ;
 }