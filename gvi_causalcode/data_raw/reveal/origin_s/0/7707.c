static void _slurm_rpc_update_block ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 update_block_msg_t * block_desc_ptr = ( update_block_msg_t * ) msg -> data ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 char * name = NULL ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_BLOCK from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, UPDATE_BLOCK RPC from uid=%d" , uid ) ;
 if ( block_desc_ptr -> bg_block_id ) {
 name = block_desc_ptr -> bg_block_id ;
 }
 else if ( block_desc_ptr -> mp_str ) {
 name = block_desc_ptr -> mp_str ;
 }
 }
 if ( error_code == SLURM_SUCCESS ) {
 if ( block_desc_ptr -> bg_block_id ) {
 error_code = select_g_update_block ( block_desc_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_update_block" ) ;
 name = block_desc_ptr -> bg_block_id ;
 }
 else if ( block_desc_ptr -> mp_str ) {
 error_code = select_g_update_sub_node ( block_desc_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_update_subbp" ) ;
 name = block_desc_ptr -> mp_str ;
 }
 else {
 error ( "Unknown update for blocks" ) ;
 error_code = SLURM_ERROR ;
 END_TIMER2 ( "_slurm_rpc_update_block" ) ;
 }
 }
 if ( error_code ) {
 info ( "_slurm_rpc_update_block %s: %s" , name , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_update_block complete for %s %s" , name , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }
 }