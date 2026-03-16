static void _slurm_rpc_update_layout ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 Buf buffer ;
 DEF_TIMERS ;
 update_layout_msg_t * msg_ptr = ( update_layout_msg_t * ) msg -> data ;
 int shrink_size ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_LAYOUT from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, UPDATE_LAYOUT RPC from uid=%d" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 buffer = init_buf ( BUF_SIZE ) ;
 packstr ( msg_ptr -> arg , buffer ) ;
 shrink_size = ( int ) get_buf_offset ( buffer ) - size_buf ( buffer ) ;
 set_buf_offset ( buffer , 0 ) ;
 grow_buf ( buffer , shrink_size ) ;
 error_code = layouts_update_layout ( msg_ptr -> layout , buffer ) ;
 free_buf ( buffer ) ;
 END_TIMER2 ( "_slurm_rpc_update_node" ) ;
 }
 if ( error_code ) {
 info ( "_slurm_rpc_update_layout for %s: %s" , msg_ptr -> layout , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_update_layout complete for %s %s" , msg_ptr -> layout , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }
 }