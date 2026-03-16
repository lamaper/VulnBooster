inline static void _slurm_rpc_set_debug_level ( slurm_msg_t * msg ) {
 int debug_level ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurmctld_lock_t config_write_lock = {
 WRITE_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 set_debug_level_msg_t * request_msg = ( set_debug_level_msg_t * ) msg -> data ;
 log_options_t log_opts = LOG_OPTS_INITIALIZER ;
 debug2 ( "Processing RPC: REQUEST_SET_DEBUG_LEVEL from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "set debug level request from non-super user uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , EACCES ) ;
 return ;
 }
 debug_level = MIN ( request_msg -> debug_level , ( LOG_LEVEL_END - 1 ) ) ;
 debug_level = MAX ( debug_level , LOG_LEVEL_QUIET ) ;
 lock_slurmctld ( config_write_lock ) ;
 if ( slurmctld_config . daemonize ) {
 log_opts . stderr_level = LOG_LEVEL_QUIET ;
 if ( slurmctld_conf . slurmctld_logfile ) {
 log_opts . logfile_level = debug_level ;
 log_opts . syslog_level = LOG_LEVEL_QUIET ;
 }
 else {
 log_opts . syslog_level = debug_level ;
 log_opts . logfile_level = LOG_LEVEL_QUIET ;
 }
 }
 else {
 log_opts . syslog_level = LOG_LEVEL_QUIET ;
 log_opts . stderr_level = debug_level ;
 if ( slurmctld_conf . slurmctld_logfile ) log_opts . logfile_level = debug_level ;
 else log_opts . logfile_level = LOG_LEVEL_QUIET ;
 }
 log_alter ( log_opts , LOG_DAEMON , slurmctld_conf . slurmctld_logfile ) ;
 unlock_slurmctld ( config_write_lock ) ;
 if ( debug_level != slurmctld_conf . slurmctld_debug ) info ( "Set debug level to %d" , debug_level ) ;
 slurmctld_conf . slurmctld_debug = debug_level ;
 slurmctld_conf . last_update = time ( NULL ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }