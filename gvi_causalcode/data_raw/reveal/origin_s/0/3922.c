inline static void _slurm_rpc_job_notify ( slurm_msg_t * msg ) {
 int error_code ;
 slurmctld_lock_t job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 job_notify_msg_t * notify_msg = ( job_notify_msg_t * ) msg -> data ;
 struct job_record * job_ptr ;
 DEF_TIMERS ;
 START_TIMER ;
 debug ( "Processing RPC: REQUEST_JOB_NOTIFY from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 job_ptr = find_job_record ( notify_msg -> job_id ) ;
 if ( ! job_ptr && ! _route_msg_to_origin ( msg , NULL , notify_msg -> job_id , uid ) ) {
 unlock_slurmctld ( job_read_lock ) ;
 return ;
 }
 if ( ! job_ptr ) error_code = ESLURM_INVALID_JOB_ID ;
 else if ( job_ptr -> batch_flag && fed_mgr_cluster_rec && job_ptr -> fed_details && fed_mgr_is_origin_job ( job_ptr ) && IS_JOB_REVOKED ( job_ptr ) && job_ptr -> fed_details -> cluster_lock && ( job_ptr -> fed_details -> cluster_lock != fed_mgr_cluster_rec -> fed . id ) ) {
 slurmdb_cluster_rec_t * dst = fed_mgr_get_cluster_by_id ( job_ptr -> fed_details -> cluster_lock ) ;
 if ( dst ) {
 slurm_send_reroute_msg ( msg , dst ) ;
 info ( "%s: %s job %d uid %d routed to %s" , __func__ , rpc_num2string ( msg -> msg_type ) , job_ptr -> job_id , uid , dst -> name ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_job_notify" ) ;
 return ;
 }
 error ( "couldn't find cluster by cluster id %d" , job_ptr -> fed_details -> cluster_lock ) ;
 error_code = ESLURM_INVALID_CLUSTER_NAME ;
 }
 else if ( ( job_ptr -> user_id == uid ) || validate_slurm_user ( uid ) ) error_code = srun_user_message ( job_ptr , notify_msg -> message ) ;
 else {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, REQUEST_JOB_NOTIFY RPC " "from uid=%d for jobid %u owner %d" , uid , notify_msg -> job_id , job_ptr -> user_id ) ;
 }
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_job_notify" ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }