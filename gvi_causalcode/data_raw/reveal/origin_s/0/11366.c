static void _slurm_rpc_update_partition ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 update_part_msg_t * part_desc_ptr = ( update_part_msg_t * ) msg -> data ;
 slurmctld_lock_t part_write_lock = {
 READ_LOCK , WRITE_LOCK , READ_LOCK , WRITE_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_PARTITION from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, UPDATE_PARTITION RPC from uid=%d" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 if ( msg -> msg_type == REQUEST_CREATE_PARTITION ) {
 lock_slurmctld ( part_write_lock ) ;
 error_code = update_part ( part_desc_ptr , true ) ;
 unlock_slurmctld ( part_write_lock ) ;
 }
 else {
 lock_slurmctld ( part_write_lock ) ;
 error_code = update_part ( part_desc_ptr , false ) ;
 unlock_slurmctld ( part_write_lock ) ;
 }
 END_TIMER2 ( "_slurm_rpc_update_partition" ) ;
 }
 if ( error_code ) {
 info ( "_slurm_rpc_update_partition partition=%s: %s" , part_desc_ptr -> name , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_update_partition complete for %s %s" , part_desc_ptr -> name , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 schedule_part_save ( ) ;
 queue_job_scheduler ( ) ;
 }
 }