static void _slurm_rpc_job_step_get_info ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 void * resp_buffer = NULL ;
 int resp_buffer_size = 0 ;
 int error_code = SLURM_SUCCESS ;
 job_step_info_request_msg_t * request = ( job_step_info_request_msg_t * ) msg -> data ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , NO_LOCK , READ_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) debug ( "Processing RPC: REQUEST_JOB_STEP_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 if ( ( request -> last_update - 1 ) >= last_job_update ) {
 unlock_slurmctld ( job_read_lock ) ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) debug ( "%s, no change" , __func__ ) ;
 error_code = SLURM_NO_CHANGE_IN_DATA ;
 }
 else {
 Buf buffer = init_buf ( BUF_SIZE ) ;
 error_code = pack_ctld_job_step_info_response_msg ( request -> job_id , request -> step_id , uid , request -> show_flags , buffer , msg -> protocol_version ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_job_step_get_info" ) ;
 if ( error_code ) {
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) debug ( "%s: %s" , __func__ , slurm_strerror ( error_code ) ) ;
 free_buf ( buffer ) ;
 }
 else {
 resp_buffer_size = get_buf_offset ( buffer ) ;
 resp_buffer = xfer_buf_data ( buffer ) ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) debug ( "%s size=%d %s" , __func__ , resp_buffer_size , TIME_STR ) ;
 }
 }
 if ( error_code ) slurm_send_rc_msg ( msg , error_code ) ;
 else {
 slurm_msg_t response_msg ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_JOB_STEP_INFO ;
 response_msg . data = resp_buffer ;
 response_msg . data_size = resp_buffer_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( resp_buffer ) ;
 }
 }