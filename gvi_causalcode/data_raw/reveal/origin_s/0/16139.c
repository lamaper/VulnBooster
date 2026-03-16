static void _slurm_rpc_reconfigure_controller ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 static bool in_progress = false ;
 DEF_TIMERS ;
 slurmctld_lock_t config_write_lock = {
 WRITE_LOCK , WRITE_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 info ( "Processing RPC: REQUEST_RECONFIGURE from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Security violation, RECONFIGURE RPC from uid=%d" , uid ) ;
 error_code = ESLURM_USER_ID_MISSING ;
 }
 if ( in_progress || slurmctld_config . shutdown_time ) error_code = EINPROGRESS ;
 if ( error_code == SLURM_SUCCESS ) {
 debug ( "sched: begin reconfiguration" ) ;
 lock_slurmctld ( config_write_lock ) ;
 in_progress = true ;
 error_code = read_slurm_conf ( 1 , true ) ;
 if ( error_code == SLURM_SUCCESS ) {
 _update_cred_key ( ) ;
 set_slurmctld_state_loc ( ) ;
 msg_to_slurmd ( REQUEST_RECONFIGURE ) ;
 }
 in_progress = false ;
 gs_reconfig ( ) ;
 unlock_slurmctld ( config_write_lock ) ;
 assoc_mgr_set_missing_uids ( ) ;
 start_power_mgr ( & slurmctld_config . thread_id_power ) ;
 trigger_reconfig ( ) ;
 }
 END_TIMER2 ( "_slurm_rpc_reconfigure_controller" ) ;
 if ( error_code ) {
 error ( "_slurm_rpc_reconfigure_controller: %s" , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 info ( "_slurm_rpc_reconfigure_controller: completed %s" , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 acct_storage_g_reconfig ( acct_db_conn , 0 ) ;
 priority_g_reconfig ( false ) ;
 save_all_state ( ) ;
 queue_job_scheduler ( ) ;
 }
 }