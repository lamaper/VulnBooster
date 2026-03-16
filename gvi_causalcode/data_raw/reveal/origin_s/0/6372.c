inline static void _slurm_rpc_dump_spank ( slurm_msg_t * msg ) {
 int rc = SLURM_SUCCESS ;
 spank_env_request_msg_t * spank_req_msg = ( spank_env_request_msg_t * ) msg -> data ;
 spank_env_responce_msg_t * spank_resp_msg = NULL ;
 slurmctld_lock_t job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurm_msg_t response_msg ;
 DEF_TIMERS ;
 START_TIMER ;
 debug ( "Processing RPC: REQUEST_SPANK_ENVIRONMENT from uid=%d JobId=%u" , uid , spank_req_msg -> job_id ) ;
 if ( ! validate_slurm_user ( uid ) ) {
 rc = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, REQUEST_SPANK_ENVIRONMENT RPC " "from uid=%d" , uid ) ;
 }
 if ( rc == SLURM_SUCCESS ) {
 struct job_record * job_ptr ;
 uint32_t i ;
 lock_slurmctld ( job_read_lock ) ;
 job_ptr = find_job_record ( spank_req_msg -> job_id ) ;
 if ( job_ptr ) {
 spank_resp_msg = xmalloc ( sizeof ( spank_env_responce_msg_t ) ) ;
 spank_resp_msg -> spank_job_env_size = job_ptr -> spank_job_env_size ;
 spank_resp_msg -> spank_job_env = xmalloc ( spank_resp_msg -> spank_job_env_size * sizeof ( char * ) ) ;
 for ( i = 0 ;
 i < spank_resp_msg -> spank_job_env_size ;
 i ++ ) spank_resp_msg -> spank_job_env [ i ] = xstrdup ( job_ptr -> spank_job_env [ i ] ) ;
 }
 else {
 rc = ESLURM_INVALID_JOB_ID ;
 }
 unlock_slurmctld ( job_read_lock ) ;
 }
 END_TIMER2 ( "_slurm_rpc_dump_spank" ) ;
 if ( rc == SLURM_SUCCESS ) {
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONCE_SPANK_ENVIRONMENT ;
 response_msg . data = spank_resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 slurm_free_spank_env_responce_msg ( spank_resp_msg ) ;
 }
 else {
 slurm_send_rc_msg ( msg , rc ) ;
 }
 }