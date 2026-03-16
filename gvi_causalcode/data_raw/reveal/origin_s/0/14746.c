static void _slurm_rpc_job_alloc_info ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 slurm_msg_t response_msg ;
 struct job_record * job_ptr ;
 DEF_TIMERS ;
 job_alloc_info_msg_t * job_info_msg = ( job_alloc_info_msg_t * ) msg -> data ;
 resource_allocation_response_msg_t * job_info_resp_msg ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_JOB_ALLOCATION_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 error_code = job_alloc_info ( uid , job_info_msg -> job_id , & job_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_job_alloc_info" ) ;
 if ( error_code || ( job_ptr == NULL ) || ( job_ptr -> job_resrcs == NULL ) ) {
 unlock_slurmctld ( job_read_lock ) ;
 debug2 ( "%s: JobId=%u, uid=%u: %s" , __func__ , job_info_msg -> job_id , uid , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug ( "%s: JobId=%u NodeList=%s %s" , __func__ , job_info_msg -> job_id , job_ptr -> nodes , TIME_STR ) ;
 job_info_resp_msg = build_job_info_resp ( job_ptr ) ;
 set_remote_working_response ( job_info_resp_msg , job_ptr , job_info_msg -> req_cluster ) ;
 unlock_slurmctld ( job_read_lock ) ;
 slurm_msg_t_init ( & response_msg ) ;
 if ( msg -> msg_type == DEFUNCT_REQUEST_JOB_ALLOCATION_INFO_LITE ) response_msg . msg_type = DEFUNCT_RESPONSE_JOB_ALLOCATION_INFO_LITE ;
 else response_msg . msg_type = RESPONSE_JOB_ALLOCATION_INFO ;
 response_msg . data = job_info_resp_msg ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 job_info_resp_msg -> working_cluster_rec = NULL ;
 slurm_free_resource_allocation_response_msg_members ( job_info_resp_msg ) ;
 xfree ( job_info_resp_msg ) ;
 }
 }