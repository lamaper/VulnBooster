static void _slurm_rpc_resv_delete ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 reservation_name_msg_t * resv_desc_ptr = ( reservation_name_msg_t * ) msg -> data ;
 slurmctld_lock_t node_write_lock = {
 NO_LOCK , READ_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_DELETE_RESERVATION from uid=%d" , uid ) ;
 if ( ! validate_operator ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, DELETE_RESERVATION RPC from uid=%d" , uid ) ;
 }
 else if ( ! resv_desc_ptr -> name ) {
 error_code = ESLURM_INVALID_PARTITION_NAME ;
 error ( "Invalid DELETE_RESERVATION RPC from uid=%d, name is null" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 lock_slurmctld ( node_write_lock ) ;
 error_code = delete_resv ( resv_desc_ptr ) ;
 unlock_slurmctld ( node_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_resv_delete" ) ;
 }
 if ( error_code ) {
 info ( "_slurm_rpc_delete_reservation partition=%s: %s" , resv_desc_ptr -> name , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 info ( "_slurm_rpc_delete_reservation complete for %s %s" , resv_desc_ptr -> name , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 queue_job_scheduler ( ) ;
 }
 }