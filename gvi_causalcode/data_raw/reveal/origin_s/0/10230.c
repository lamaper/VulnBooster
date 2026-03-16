static void _slurm_rpc_shutdown_controller ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS , i ;
 uint16_t options = 0 ;
 shutdown_msg_t * shutdown_msg = ( shutdown_msg_t * ) msg -> data ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurmctld_lock_t node_read_lock = {
 NO_LOCK , NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Security violation, SHUTDOWN RPC from uid=%d" , uid ) ;
 error_code = ESLURM_USER_ID_MISSING ;
 }
 if ( error_code ) ;
 else if ( msg -> msg_type == REQUEST_CONTROL ) {
 info ( "Performing RPC: REQUEST_CONTROL" ) ;
 slurmctld_config . resume_backup = true ;
 }
 else {
 info ( "Performing RPC: REQUEST_SHUTDOWN" ) ;
 options = shutdown_msg -> options ;
 }
 if ( error_code ) ;
 else if ( options == 1 ) info ( "performing immeditate shutdown without state save" ) ;
 else if ( slurmctld_config . shutdown_time ) debug2 ( "shutdown RPC issued when already in progress" ) ;
 else {
 if ( ( msg -> msg_type == REQUEST_SHUTDOWN ) && ( options == 0 ) ) {
 lock_slurmctld ( node_read_lock ) ;
 msg_to_slurmd ( REQUEST_SHUTDOWN ) ;
 unlock_slurmctld ( node_read_lock ) ;
 }
 if ( slurmctld_config . thread_id_sig ) pthread_kill ( slurmctld_config . thread_id_sig , SIGTERM ) ;
 else {
 error ( "thread_id_sig undefined, hard shutdown" ) ;
 slurmctld_config . shutdown_time = time ( NULL ) ;
 slurmctld_shutdown ( ) ;
 }
 }
 if ( msg -> msg_type == REQUEST_CONTROL ) {
 for ( i = 1 ;
 i < ( CONTROL_TIMEOUT * 10 ) ;
 i ++ ) {
 if ( slurmctld_config . server_thread_count <= 1 ) break ;
 usleep ( 100000 ) ;
 }
 if ( slurmctld_config . server_thread_count > 1 ) error ( "REQUEST_CONTROL reply with %d active threads" , slurmctld_config . server_thread_count ) ;
 ( void ) g_slurm_jobcomp_fini ( ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 if ( ( error_code == SLURM_SUCCESS ) && ( options == 1 ) && ( slurmctld_config . thread_id_sig ) ) pthread_kill ( slurmctld_config . thread_id_sig , SIGABRT ) ;
 }