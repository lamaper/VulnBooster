static void _slurm_rpc_job_pack_alloc_info ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 slurm_msg_t response_msg ;
 struct job_record * job_ptr , * pack_job ;
 ListIterator iter ;
 void * working_cluster_rec = NULL ;
 List resp ;
 DEF_TIMERS ;
 job_alloc_info_msg_t * job_info_msg = ( job_alloc_info_msg_t * ) msg -> data ;
 resource_allocation_response_msg_t * job_info_resp_msg ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_JOB_PACK_ALLOC_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 error_code = job_alloc_info ( uid , job_info_msg -> job_id , & job_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_job_pack_alloc_info" ) ;
 if ( ( error_code == SLURM_SUCCESS ) && job_ptr && ( job_ptr -> pack_job_id && ! job_ptr -> pack_job_list ) ) error_code = ESLURM_NOT_PACK_JOB_LEADER ;
 if ( error_code || ( job_ptr == NULL ) || ( job_ptr -> job_resrcs == NULL ) ) {
 unlock_slurmctld ( job_read_lock ) ;
 debug2 ( "%s: JobId=%u, uid=%u: %s" , __func__ , job_info_msg -> job_id , uid , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 return ;
 }
 debug ( "%s: JobId=%u NodeList=%s %s" , __func__ , job_info_msg -> job_id , job_ptr -> nodes , TIME_STR ) ;
 if ( ! job_ptr -> pack_job_list ) {
 resp = list_create ( _pack_alloc_list_del ) ;
 job_info_resp_msg = build_job_info_resp ( job_ptr ) ;
 set_remote_working_response ( job_info_resp_msg , job_ptr , job_info_msg -> req_cluster ) ;
 list_append ( resp , job_info_resp_msg ) ;
 }
 else {
 resp = list_create ( _pack_alloc_list_del ) ;
 iter = list_iterator_create ( job_ptr -> pack_job_list ) ;
 while ( ( pack_job = ( struct job_record * ) list_next ( iter ) ) ) {
 if ( job_ptr -> pack_job_id != pack_job -> pack_job_id ) {
 error ( "%s: Bad pack_job_list for job %u" , __func__ , job_ptr -> pack_job_id ) ;
 continue ;
 }
 if ( pack_job -> job_id != job_info_msg -> job_id ) ( void ) job_alloc_info_ptr ( uid , pack_job ) ;
 job_info_resp_msg = build_job_info_resp ( pack_job ) ;
 if ( working_cluster_rec ) {
 job_info_resp_msg -> working_cluster_rec = working_cluster_rec ;
 }
 else {
 set_remote_working_response ( job_info_resp_msg , pack_job , job_info_msg -> req_cluster ) ;
 working_cluster_rec = job_info_resp_msg -> working_cluster_rec ;
 }
 list_append ( resp , job_info_resp_msg ) ;
 }
 list_iterator_destroy ( iter ) ;
 }
 unlock_slurmctld ( job_read_lock ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . msg_type = RESPONSE_JOB_PACK_ALLOCATION ;
 response_msg . data = resp ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 FREE_NULL_LIST ( resp ) ;
 }