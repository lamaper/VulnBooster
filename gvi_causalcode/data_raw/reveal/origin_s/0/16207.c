static void _slurm_rpc_step_complete ( slurm_msg_t * msg , bool running_composite ) {
 static int active_rpc_cnt = 0 ;
 int error_code = SLURM_SUCCESS , rc , rem ;
 uint32_t step_rc ;
 DEF_TIMERS ;
 step_complete_msg_t * req = ( step_complete_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 bool dump_job = false ;
 START_TIMER ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "Processing RPC: REQUEST_STEP_COMPLETE for %u.%u " "nodes %u-%u rc=%u uid=%d" , req -> job_id , req -> job_step_id , req -> range_first , req -> range_last , req -> step_rc , uid ) ;
 if ( ! running_composite ) {
 _throttle_start ( & active_rpc_cnt ) ;
 lock_slurmctld ( job_write_lock ) ;
 }
 rc = step_partial_comp ( req , uid , & rem , & step_rc ) ;
 if ( rc || rem ) {
 if ( ! running_composite ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 }
 slurm_send_rc_msg ( msg , rc ) ;
 if ( ! rc ) schedule_job_save ( ) ;
 return ;
 }
 if ( req -> job_step_id == SLURM_BATCH_SCRIPT ) {
 error_code = job_complete ( req -> job_id , uid , false , false , step_rc ) ;
 if ( ! running_composite ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 }
 END_TIMER2 ( "_slurm_rpc_step_complete" ) ;
 if ( error_code ) {
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "%s JobId=%u: %s" , __func__ , req -> job_id , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "sched: %s JobId=%u: %s" , __func__ , req -> job_id , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 dump_job = true ;
 }
 }
 else {
 error_code = job_step_complete ( req -> job_id , req -> job_step_id , uid , false , step_rc ) ;
 if ( ! running_composite ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 }
 END_TIMER2 ( "_slurm_rpc_step_complete" ) ;
 if ( error_code ) {
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "%s 1 StepId=%u.%u %s" , __func__ , req -> job_id , req -> job_step_id , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "sched: %s StepId=%u.%u %s" , __func__ , req -> job_id , req -> job_step_id , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 dump_job = true ;
 }
 }
 if ( dump_job ) ( void ) schedule_job_save ( ) ;
 }