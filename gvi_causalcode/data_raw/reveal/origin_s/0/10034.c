inline static void _slurm_rpc_set_debug_flags ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurmctld_lock_t config_write_lock = {
 WRITE_LOCK , READ_LOCK , READ_LOCK , READ_LOCK , READ_LOCK }
 ;
 set_debug_flags_msg_t * request_msg = ( set_debug_flags_msg_t * ) msg -> data ;
 uint64_t debug_flags ;
 char * flag_string ;
 debug2 ( "Processing RPC: REQUEST_SET_DEBUG_FLAGS from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "set debug flags request from non-super user uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , EACCES ) ;
 return ;
 }
 lock_slurmctld ( config_write_lock ) ;
 debug_flags = slurmctld_conf . debug_flags ;
 debug_flags &= ( ~ request_msg -> debug_flags_minus ) ;
 debug_flags |= request_msg -> debug_flags_plus ;
 slurm_set_debug_flags ( debug_flags ) ;
 slurmctld_conf . last_update = time ( NULL ) ;
 log_set_debug_flags ( ) ;
 gs_reconfig ( ) ;
 gres_plugin_reconfig ( NULL ) ;
 acct_storage_g_reconfig ( acct_db_conn , 0 ) ;
 priority_g_reconfig ( false ) ;
 select_g_reconfigure ( ) ;
 ( void ) slurm_sched_g_reconfig ( ) ;
 ( void ) switch_g_reconfig ( ) ;
 unlock_slurmctld ( config_write_lock ) ;
 flag_string = debug_flags2str ( debug_flags ) ;
 info ( "Set DebugFlags to %s" , flag_string ? flag_string : "none" ) ;
 xfree ( flag_string ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }