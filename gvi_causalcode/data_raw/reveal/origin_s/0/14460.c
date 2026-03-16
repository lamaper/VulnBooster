static void _slurm_rpc_dump_conf ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 slurm_msg_t response_msg ;
 last_update_msg_t * last_time_msg = ( last_update_msg_t * ) msg -> data ;
 slurm_ctl_conf_info_msg_t config_tbl ;
 slurmctld_lock_t config_read_lock = {
 READ_LOCK , READ_LOCK , NO_LOCK , READ_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_BUILD_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( config_read_lock ) ;
 if ( ( last_time_msg -> last_update - 1 ) >= slurmctld_conf . last_update ) {
 unlock_slurmctld ( config_read_lock ) ;
 debug2 ( "_slurm_rpc_dump_conf, no change" ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 }
 else {
 _fill_ctld_conf ( & config_tbl ) ;
 unlock_slurmctld ( config_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_conf" ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_BUILD_INFO ;
 response_msg . data = & config_tbl ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 free_slurm_conf ( & config_tbl , false ) ;
 }
 }