static void _slurm_rpc_node_registration ( slurm_msg_t * msg , bool running_composite ) {
 DEF_TIMERS ;
 int error_code = SLURM_SUCCESS ;
 bool newly_up = false ;
 slurm_node_registration_status_msg_t * node_reg_stat_msg = ( slurm_node_registration_status_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 READ_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: MESSAGE_NODE_REGISTRATION_STATUS from uid=%d" , uid ) ;
 if ( ! validate_slurm_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, NODE_REGISTER RPC from uid=%d" , uid ) ;
 }
 if ( msg -> protocol_version != SLURM_PROTOCOL_VERSION ) info ( "Node %s appears to have a different version " "of Slurm than ours. Please update at your earliest " "convenience." , node_reg_stat_msg -> node_name ) ;
 if ( error_code == SLURM_SUCCESS ) {
 if ( ! ( slurmctld_conf . debug_flags & DEBUG_FLAG_NO_CONF_HASH ) && ( node_reg_stat_msg -> hash_val != NO_VAL ) && ( node_reg_stat_msg -> hash_val != slurm_get_hash_val ( ) ) ) {
 error ( "Node %s appears to have a different slurm.conf " "than the slurmctld. This could cause issues " "with communication and functionality. " "Please review both files and make sure they " "are the same. If this is expected ignore, and " "set DebugFlags=NO_CONF_HASH in your slurm.conf." , node_reg_stat_msg -> node_name ) ;
 }
 if ( ! running_composite ) lock_slurmctld ( job_write_lock ) ;


 error_code = validate_node_specs ( node_reg_stat_msg , msg -> protocol_version , & newly_up ) ;

 END_TIMER2 ( "_slurm_rpc_node_registration" ) ;
 if ( newly_up ) {
 queue_job_scheduler ( ) ;
 }
 }
 if ( error_code ) {
 error ( "_slurm_rpc_node_registration node=%s: %s" , node_reg_stat_msg -> node_name , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_node_registration complete for %s %s" , node_reg_stat_msg -> node_name , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }
 }