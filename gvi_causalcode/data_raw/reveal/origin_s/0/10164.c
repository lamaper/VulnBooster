static void _slurm_rpc_end_time ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 job_alloc_info_msg_t * time_req_msg = ( job_alloc_info_msg_t * ) msg -> data ;
 srun_timeout_msg_t timeout_msg ;
 slurm_msg_t response_msg ;
 int rc ;
 slurmctld_lock_t job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_JOB_END_TIME from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 rc = job_end_time ( time_req_msg , & timeout_msg ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_end_time" ) ;
 if ( rc != SLURM_SUCCESS ) {
 slurm_send_rc_msg ( msg , rc ) ;
 }
 else {
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = SRUN_TIMEOUT ;
 response_msg . data = & timeout_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 }
 debug2 ( "_slurm_rpc_end_time jobid=%u %s" , time_req_msg -> job_id , TIME_STR ) ;
 }