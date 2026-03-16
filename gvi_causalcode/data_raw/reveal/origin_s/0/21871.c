static void _slurm_rpc_resv_update ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 resv_desc_msg_t * resv_desc_ptr = ( resv_desc_msg_t * ) msg -> data ;
 slurmctld_lock_t node_write_lock = {
 READ_LOCK , READ_LOCK , WRITE_LOCK , READ_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_RESERVATION from uid=%d" , uid ) ;
 if ( ! validate_operator ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, UPDATE_RESERVATION RPC from uid=%d" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 lock_slurmctld ( node_write_lock ) ;
 error_code = update_resv ( resv_desc_ptr ) ;
 unlock_slurmctld ( node_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_resv_update" ) ;
 }
 if ( error_code ) {
 info ( "_slurm_rpc_resv_update reservation=%s: %s" , resv_desc_ptr -> name , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_resv_update complete for %s %s" , resv_desc_ptr -> name , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 queue_job_scheduler ( ) ;
 }
 }