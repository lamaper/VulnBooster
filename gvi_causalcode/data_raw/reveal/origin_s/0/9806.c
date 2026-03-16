static void _slurm_rpc_takeover ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Security violation, TAKEOVER RPC from uid=%d" , uid ) ;
 error_code = ESLURM_USER_ID_MISSING ;
 }
 else {
 info ( "Performing RPC: REQUEST_TAKEOVER : " "already in controller mode - skipping" ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 }