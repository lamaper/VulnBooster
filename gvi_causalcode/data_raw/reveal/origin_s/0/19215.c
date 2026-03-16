static void _slurm_rpc_update_front_end ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 update_front_end_msg_t * update_front_end_msg_ptr = ( update_front_end_msg_t * ) msg -> data ;
 slurmctld_lock_t node_write_lock = {
 NO_LOCK , NO_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_FRONT_END from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, UPDATE_FRONT_END RPC from uid=%d" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 lock_slurmctld ( node_write_lock ) ;
 error_code = update_front_end ( update_front_end_msg_ptr ) ;
 unlock_slurmctld ( node_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_update_front_end" ) ;
 }
 if ( error_code ) {
 info ( "_slurm_rpc_update_front_end for %s: %s" , update_front_end_msg_ptr -> name , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_update_front_end complete for %s %s" , update_front_end_msg_ptr -> name , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }
 }