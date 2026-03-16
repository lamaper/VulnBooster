inline static void _slurm_rpc_top_job ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 top_job_msg_t * top_ptr = ( top_job_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 debug ( "Processing RPC: REQUEST_TOP_JOB from uid=%u" , ( unsigned int ) uid ) ;
 START_TIMER ;
 lock_slurmctld ( job_write_lock ) ;
 error_code = job_set_top ( top_ptr , uid , msg -> conn_fd , msg -> protocol_version ) ;
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_top" ) ;
 if ( error_code ) {
 info ( "%s for %s %s" , __func__ , top_ptr -> job_id_str , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "%s for %s %s" , __func__ , top_ptr -> job_id_str , TIME_STR ) ;
 }
 }