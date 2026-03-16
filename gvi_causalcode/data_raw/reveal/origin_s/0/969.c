static void _slurm_rpc_update_powercap ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 bool valid_cap = false ;
 uint32_t min , max , orig_cap ;
 update_powercap_msg_t * ptr = ( update_powercap_msg_t * ) msg -> data ;
 slurmctld_lock_t config_write_lock = {
 WRITE_LOCK , NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_POWERCAP from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, UPDATE_POWERCAP RPC from uid=%d" , uid ) ;
 }
 if ( error_code == SLURM_SUCCESS ) {
 lock_slurmctld ( config_write_lock ) ;
 if ( ptr -> power_cap == 0 || ptr -> power_cap == INFINITE ) {
 valid_cap = true ;
 }
 else if ( ! power_layout_ready ( ) ) {
 valid_cap = true ;
 }
 else {
 orig_cap = powercap_get_cluster_current_cap ( ) ;
 powercap_set_cluster_cap ( INFINITE ) ;
 min = powercap_get_cluster_min_watts ( ) ;
 max = powercap_get_cluster_max_watts ( ) ;
 if ( min <= ptr -> power_cap && max >= ptr -> power_cap ) valid_cap = true ;
 else powercap_set_cluster_cap ( orig_cap ) ;
 }
 if ( valid_cap ) powercap_set_cluster_cap ( ptr -> power_cap ) ;
 else error_code = ESLURM_INVALID_POWERCAP ;
 unlock_slurmctld ( config_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_update_powercap" ) ;
 }
 if ( error_code ) {
 info ( "_slurm_rpc_update_powercap: %s" , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_update_powercap complete %s" , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 if ( ! LOTS_OF_AGENTS ) schedule ( 0 ) ;
 save_all_state ( ) ;
 }
 }