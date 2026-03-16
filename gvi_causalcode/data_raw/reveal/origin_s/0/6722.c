static void _slurm_rpc_job_step_kill ( uint32_t uid , slurm_msg_t * msg ) {
 static int active_rpc_cnt = 0 ;
 int error_code = SLURM_SUCCESS ;
 job_step_kill_msg_t * job_step_kill_msg = ( job_step_kill_msg_t * ) msg -> data ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) {
 info ( "Processing RPC: REQUEST_CANCEL_JOB_STEP %u.%u uid=%u" , job_step_kill_msg -> job_id , job_step_kill_msg -> job_step_id , uid ) ;
 }
 _throttle_start ( & active_rpc_cnt ) ;
 error_code = kill_job_step ( job_step_kill_msg , uid ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }