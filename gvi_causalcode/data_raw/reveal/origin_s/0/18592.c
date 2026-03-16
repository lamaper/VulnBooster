inline static void _slurm_rpc_set_schedlog_level ( slurm_msg_t * msg ) {
 int schedlog_level ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurmctld_lock_t config_read_lock = {
 READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 set_debug_level_msg_t * request_msg = ( set_debug_level_msg_t * ) msg -> data ;
 log_options_t log_opts = SCHEDLOG_OPTS_INITIALIZER ;
 debug2 ( "Processing RPC: REQUEST_SET_SCHEDLOG_LEVEL from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "set scheduler log level request from non-super user " "uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , EACCES ) ;
 return ;
 }
 if ( slurmctld_conf . sched_logfile == NULL ) {
 error ( "set scheduler log level failed: no log file!" ) ;
 slurm_send_rc_msg ( msg , ESLURM_DISABLED ) ;
 return ;
 }
 schedlog_level = MIN ( request_msg -> debug_level , ( LOG_LEVEL_QUIET + 1 ) ) ;
 schedlog_level = MAX ( schedlog_level , LOG_LEVEL_QUIET ) ;
 lock_slurmctld ( config_read_lock ) ;
 log_opts . logfile_level = schedlog_level ;
 sched_log_alter ( log_opts , LOG_DAEMON , slurmctld_conf . sched_logfile ) ;
 unlock_slurmctld ( config_read_lock ) ;
 if ( schedlog_level != slurmctld_conf . sched_log_level ) info ( "sched: Set scheduler log level to %d" , schedlog_level ) ;
 slurmctld_conf . sched_log_level = schedlog_level ;
 slurmctld_conf . last_update = time ( NULL ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }