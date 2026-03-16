static void _slurm_rpc_step_layout ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 slurm_msg_t response_msg ;
 DEF_TIMERS ;
 job_step_id_msg_t * req = ( job_step_id_msg_t * ) msg -> data ;
 slurm_step_layout_t * step_layout = NULL ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 struct job_record * job_ptr = NULL ;
 struct step_record * step_ptr = NULL ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_STEP_LAYOUT, from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 error_code = job_alloc_info ( uid , req -> job_id , & job_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_step_layout" ) ;
 if ( error_code || ( job_ptr == NULL ) ) {
 unlock_slurmctld ( job_read_lock ) ;
 if ( error_code == ESLURM_ACCESS_DENIED ) {
 error ( "Security vioation, REQUEST_STEP_LAYOUT for " "JobId=%u from uid=%u" , req -> job_id , uid ) ;
 }
 else {
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "%s: JobId=%u, uid=%u: %s" , __func__ , req -> job_id , uid , slurm_strerror ( error_code ) ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 return ;
 }
 step_ptr = find_step_record ( job_ptr , req -> step_id ) ;
 if ( ! step_ptr ) {
 unlock_slurmctld ( job_read_lock ) ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "%s: JobId=%u.%u Not Found" , __func__ , req -> job_id , req -> step_id ) ;
 slurm_send_rc_msg ( msg , ESLURM_INVALID_JOB_ID ) ;
 return ;
 }
 step_layout = slurm_step_layout_copy ( step_ptr -> step_layout ) ;


 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . msg_type = RESPONSE_STEP_LAYOUT ;
 response_msg . data = step_layout ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 slurm_step_layout_destroy ( step_layout ) ;
 }