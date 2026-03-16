static void _slurm_rpc_shutdown_controller_immediate ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Security violation, SHUTDOWN_IMMEDIATE RPC from uid=%d" , uid ) ;
 error_code = ESLURM_USER_ID_MISSING ;
 }
 if ( error_code == SLURM_SUCCESS ) debug ( "Performing RPC: REQUEST_SHUTDOWN_IMMEDIATE" ) ;
 }