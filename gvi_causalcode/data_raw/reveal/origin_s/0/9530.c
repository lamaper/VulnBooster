static void _slurm_rpc_dump_batch_script ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 int rc = SLURM_SUCCESS ;
 slurm_msg_t response_msg ;
 struct job_record * job_ptr ;
 char * script ;
 job_id_msg_t * job_id_msg = ( job_id_msg_t * ) msg -> data ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug3 ( "Processing RPC: REQUEST_BATCH_SCRIPT from uid=%d for job=%u" , uid , job_id_msg -> job_id ) ;
 lock_slurmctld ( job_read_lock ) ;
 if ( ( job_ptr = find_job_record ( job_id_msg -> job_id ) ) ) {
 if ( ! validate_operator ( uid ) && job_ptr -> user_id != uid ) {
 rc = ESLURM_USER_ID_MISSING ;
 }
 else {
 script = get_job_script ( job_ptr ) ;
 if ( ! script ) rc = ESLURM_JOB_SCRIPT_MISSING ;
 }
 }
 else {
 rc = ESLURM_INVALID_JOB_ID ;
 }
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_batch_script" ) ;
 if ( rc != SLURM_SUCCESS ) {
 slurm_send_rc_msg ( msg , rc ) ;
 }
 else {
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_BATCH_SCRIPT ;
 response_msg . data = script ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( script ) ;
 }
 }