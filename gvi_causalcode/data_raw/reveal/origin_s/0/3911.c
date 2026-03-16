inline static void _slurm_rpc_requeue ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 requeue_msg_t * req_ptr = ( requeue_msg_t * ) msg -> data ;
 slurmctld_lock_t fed_read_lock = {
 NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , READ_LOCK }
 ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 lock_slurmctld ( fed_read_lock ) ;
 if ( ! _route_msg_to_origin ( msg , req_ptr -> job_id_str , req_ptr -> job_id , uid ) ) {
 unlock_slurmctld ( fed_read_lock ) ;
 return ;
 }
 unlock_slurmctld ( fed_read_lock ) ;
 START_TIMER ;
 info ( "%s: Processing RPC: REQUEST_JOB_REQUEUE from uid=%d" , __func__ , uid ) ;
 lock_slurmctld ( job_write_lock ) ;
 if ( req_ptr -> job_id_str ) {
 error_code = job_requeue2 ( uid , req_ptr , msg , false ) ;
 }
 else {
 error_code = job_requeue ( uid , req_ptr -> job_id , msg , false , req_ptr -> state ) ;
 }
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_requeue" ) ;
 if ( error_code ) {
 if ( ! req_ptr -> job_id_str ) xstrfmtcat ( req_ptr -> job_id_str , "%u" , req_ptr -> job_id ) ;
 info ( "%s: %s: %s" , __func__ , req_ptr -> job_id_str , slurm_strerror ( error_code ) ) ;
 }
 schedule_job_save ( ) ;
 }