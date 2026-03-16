static void _slurm_rpc_event_log ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurm_event_log_msg_t * event_log_msg ;
 int error_code = SLURM_SUCCESS ;
 event_log_msg = ( slurm_event_log_msg_t * ) msg -> data ;
 if ( ! validate_slurm_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, REQUEST_EVENT_LOG from uid=%d" , uid ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_ERROR ) {
 error ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_INFO ) {
 info ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_VERBOSE ) {
 verbose ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_DEBUG ) {
 debug ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_DEBUG2 ) {
 debug2 ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_DEBUG3 ) {
 debug3 ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_DEBUG4 ) {
 debug4 ( "%s" , event_log_msg -> string ) ;
 }
 else if ( event_log_msg -> level == LOG_LEVEL_DEBUG5 ) {
 debug5 ( "%s" , event_log_msg -> string ) ;
 }
 else {
 error_code = EINVAL ;
 error ( "Invalid message level: %u" , event_log_msg -> level ) ;
 error ( "%s" , event_log_msg -> string ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 }