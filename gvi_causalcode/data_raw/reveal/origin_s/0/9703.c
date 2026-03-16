static void _slurm_rpc_epilog_complete ( slurm_msg_t * msg , bool * run_scheduler , bool running_composite ) {
 static int active_rpc_cnt = 0 ;
 static time_t config_update = 0 ;
 static bool defer_sched = false ;
 DEF_TIMERS ;
 slurmctld_lock_t job_write_lock = {
 READ_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 epilog_complete_msg_t * epilog_msg = ( epilog_complete_msg_t * ) msg -> data ;
 struct job_record * job_ptr ;
 char jbuf [ JBUFSIZ ] ;
 START_TIMER ;
 debug2 ( "Processing RPC: MESSAGE_EPILOG_COMPLETE uid=%d" , uid ) ;
 if ( ! validate_slurm_user ( uid ) ) {
 error ( "Security violation, EPILOG_COMPLETE RPC from uid=%d" , uid ) ;
 return ;
 }
 if ( ! running_composite ) {
 if ( config_update != slurmctld_conf . last_update ) {
 char * sched_params = slurm_get_sched_params ( ) ;
 defer_sched = ( sched_params && strstr ( sched_params , "defer" ) ) ;
 xfree ( sched_params ) ;
 config_update = slurmctld_conf . last_update ;
 }
 _throttle_start ( & active_rpc_cnt ) ;
 lock_slurmctld ( job_write_lock ) ;
 }
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_ROUTE ) info ( "_slurm_rpc_epilog_complete: " "node_name = %s, job_id = %u" , epilog_msg -> node_name , epilog_msg -> job_id ) ;
 if ( job_epilog_complete ( epilog_msg -> job_id , epilog_msg -> node_name , epilog_msg -> return_code ) ) * run_scheduler = true ;
 job_ptr = find_job_record ( epilog_msg -> job_id ) ;
 if ( epilog_msg -> return_code ) error ( "%s: epilog error %s Node=%s Err=%s %s" , __func__ , jobid2str ( job_ptr , jbuf , sizeof ( jbuf ) ) , epilog_msg -> node_name , slurm_strerror ( epilog_msg -> return_code ) , TIME_STR ) ;
 else debug2 ( "%s: %s Node=%s %s" , __func__ , jobid2str ( job_ptr , jbuf , sizeof ( jbuf ) ) , epilog_msg -> node_name , TIME_STR ) ;
 if ( ! running_composite ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 }
 END_TIMER2 ( "_slurm_rpc_epilog_complete" ) ;
 if ( ! running_composite && * run_scheduler ) {
 if ( ! LOTS_OF_AGENTS && ! defer_sched ) ( void ) schedule ( 0 ) ;
 schedule_node_save ( ) ;
 schedule_job_save ( ) ;
 }
 }