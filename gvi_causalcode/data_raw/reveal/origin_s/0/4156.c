static void _slurm_rpc_job_ready ( slurm_msg_t * msg ) {
 int error_code , result ;
 job_id_msg_t * id_msg = ( job_id_msg_t * ) msg -> data ;
 DEF_TIMERS ;
 slurmctld_lock_t job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 slurm_msg_t response_msg ;
 return_code_msg_t rc_msg ;
 START_TIMER ;
 lock_slurmctld ( job_read_lock ) ;
 error_code = job_node_ready ( id_msg -> job_id , & result ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_job_ready" ) ;
 if ( error_code ) {
 debug2 ( "_slurm_rpc_job_ready: %s" , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_job_ready(%u)=%d %s" , id_msg -> job_id , result , TIME_STR ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 rc_msg . return_code = result ;
 response_msg . data = & rc_msg ;
 if ( _is_prolog_finished ( id_msg -> job_id ) ) {
 response_msg . msg_type = RESPONSE_JOB_READY ;
 }
 else {
 response_msg . msg_type = RESPONSE_PROLOG_EXECUTING ;
 }
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 }
 }