inline static void _slurm_rpc_suspend ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 suspend_msg_t * sus_ptr = ( suspend_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 struct job_record * job_ptr ;
 char * op ;
 START_TIMER ;
 switch ( sus_ptr -> op ) {
 case SUSPEND_JOB : op = "suspend" ;
 break ;
 case RESUME_JOB : op = "resume" ;
 break ;
 default : op = "unknown" ;
 }
 info ( "Processing RPC: REQUEST_SUSPEND(%s) from uid=%u" , op , ( unsigned int ) uid ) ;
 if ( ( sus_ptr -> job_id == NO_VAL ) && sus_ptr -> job_id_str ) sus_ptr -> job_id = strtol ( sus_ptr -> job_id_str , NULL , 10 ) ;
 lock_slurmctld ( job_write_lock ) ;
 job_ptr = find_job_record ( sus_ptr -> job_id ) ;
 if ( ! job_ptr && ! _route_msg_to_origin ( msg , NULL , sus_ptr -> job_id , uid ) ) {
 unlock_slurmctld ( job_write_lock ) ;
 return ;
 }
 if ( ! job_ptr ) error_code = ESLURM_INVALID_JOB_ID ;
 else if ( fed_mgr_cluster_rec && job_ptr -> fed_details && fed_mgr_is_origin_job ( job_ptr ) && IS_JOB_REVOKED ( job_ptr ) && job_ptr -> fed_details -> cluster_lock && ( job_ptr -> fed_details -> cluster_lock != fed_mgr_cluster_rec -> fed . id ) ) {
 slurmdb_cluster_rec_t * dst = fed_mgr_get_cluster_by_id ( job_ptr -> fed_details -> cluster_lock ) ;
 if ( dst ) {
 slurm_send_reroute_msg ( msg , dst ) ;
 info ( "%s: %s job %d uid %d routed to %s" , __func__ , rpc_num2string ( msg -> msg_type ) , job_ptr -> job_id , uid , dst -> name ) ;
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_suspend" ) ;
 return ;
 }
 error ( "couldn't find cluster by cluster id %d" , job_ptr -> fed_details -> cluster_lock ) ;
 error_code = ESLURM_INVALID_CLUSTER_NAME ;
 }
 else if ( sus_ptr -> job_id_str ) {
 error_code = job_suspend2 ( sus_ptr , uid , msg -> conn_fd , true , msg -> protocol_version ) ;
 }
 else {
 error_code = job_suspend ( sus_ptr , uid , msg -> conn_fd , true , msg -> protocol_version ) ;
 }
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_suspend" ) ;
 if ( ! sus_ptr -> job_id_str ) xstrfmtcat ( sus_ptr -> job_id_str , "%u" , sus_ptr -> job_id ) ;
 if ( error_code ) {
 info ( "_slurm_rpc_suspend(%s) for %s %s" , op , sus_ptr -> job_id_str , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "_slurm_rpc_suspend(%s) for %s %s" , op , sus_ptr -> job_id_str , TIME_STR ) ;
 schedule_job_save ( ) ;
 if ( sus_ptr -> op == SUSPEND_JOB ) queue_job_scheduler ( ) ;
 }
 }