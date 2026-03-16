static void _slurm_rpc_resv_create ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 resv_desc_msg_t * resv_desc_ptr = ( resv_desc_msg_t * ) msg -> data ;
 slurmctld_lock_t node_write_lock = {
 READ_LOCK , READ_LOCK , WRITE_LOCK , READ_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_CREATE_RESERVATION from uid=%d" , uid ) ;
 if ( ! validate_operator ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, CREATE_RESERVATION RPC from uid=%d" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 lock_slurmctld ( node_write_lock ) ;
 error_code = create_resv ( resv_desc_ptr ) ;
 unlock_slurmctld ( node_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_resv_create" ) ;
 }
 if ( error_code ) {
 if ( resv_desc_ptr -> name ) {
 info ( "_slurm_rpc_resv_create reservation=%s: %s" , resv_desc_ptr -> name , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "_slurm_rpc_resv_create: %s" , slurm_strerror ( error_code ) ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 slurm_msg_t response_msg ;
 reservation_name_msg_t resv_resp_msg ;
 debug2 ( "_slurm_rpc_resv_create complete for %s %s" , resv_desc_ptr -> name , TIME_STR ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 resv_resp_msg . name = resv_desc_ptr -> name ;
 response_msg . msg_type = RESPONSE_CREATE_RESERVATION ;
 response_msg . data = & resv_resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 queue_job_scheduler ( ) ;
 }
 }