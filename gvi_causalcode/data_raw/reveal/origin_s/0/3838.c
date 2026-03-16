static void _slurm_rpc_burst_buffer_info ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 void * resp_buffer = NULL ;
 int resp_buffer_size = 0 ;
 int error_code = SLURM_SUCCESS ;
 Buf buffer ;
 DEF_TIMERS ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_BURST_BUFFER_INFO from uid=%d" , uid ) ;
 buffer = init_buf ( BUF_SIZE ) ;
 if ( validate_super_user ( uid ) ) uid = 0 ;
 error_code = bb_g_state_pack ( uid , buffer , msg -> protocol_version ) ;
 END_TIMER2 ( __func__ ) ;
 if ( error_code ) {
 debug ( "_slurm_rpc_burst_buffer_info: %s" , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 slurm_msg_t response_msg ;
 resp_buffer_size = get_buf_offset ( buffer ) ;
 resp_buffer = xfer_buf_data ( buffer ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_BURST_BUFFER_INFO ;
 response_msg . data = resp_buffer ;
 response_msg . data_size = resp_buffer_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( resp_buffer ) ;
 }
 }