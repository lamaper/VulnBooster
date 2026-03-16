static void _slurm_rpc_block_info ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 Buf buffer = NULL ;
 block_info_request_msg_t * sel_req_msg = ( block_info_request_msg_t * ) msg -> data ;
 slurm_msg_t response_msg ;
 slurmctld_lock_t config_read_lock = {
 READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 DEF_TIMERS ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_BLOCK_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( config_read_lock ) ;
 if ( ( slurmctld_conf . private_data & PRIVATE_DATA_NODES ) && ! validate_operator ( uid ) ) {
 error_code = ESLURM_ACCESS_DENIED ;
 error ( "Security violation, REQUEST_BLOCK_INFO RPC from uid=%d" , uid ) ;
 }
 unlock_slurmctld ( config_read_lock ) ;
 if ( error_code == SLURM_SUCCESS ) {
 error_code = select_g_pack_select_info ( sel_req_msg -> last_update , sel_req_msg -> show_flags , & buffer , msg -> protocol_version ) ;
 }
 END_TIMER2 ( "_slurm_rpc_block_info" ) ;
 if ( error_code ) {
 debug3 ( "_slurm_rpc_block_info: %s" , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_BLOCK_INFO ;
 response_msg . data = get_buf_data ( buffer ) ;
 response_msg . data_size = get_buf_offset ( buffer ) ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 free_buf ( buffer ) ;
 }
 }