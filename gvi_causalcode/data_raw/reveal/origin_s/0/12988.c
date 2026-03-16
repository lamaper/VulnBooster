static void _slurm_rpc_complete_job_allocation ( slurm_msg_t * msg ) {
 static int active_rpc_cnt = 0 ;
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 complete_job_allocation_msg_t * comp_msg = ( complete_job_allocation_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 struct job_record * job_ptr ;
 char jbuf [ JBUFSIZ ] ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_COMPLETE_JOB_ALLOCATION from " "uid=%u, JobId=%u rc=%d" , uid , comp_msg -> job_id , comp_msg -> job_rc ) ;
 _throttle_start ( & active_rpc_cnt ) ;
 lock_slurmctld ( job_write_lock ) ;
 job_ptr = find_job_record ( comp_msg -> job_id ) ;
 trace_job ( job_ptr , __func__ , "enter" ) ;
 error_code = job_complete ( comp_msg -> job_id , uid , false , false , comp_msg -> job_rc ) ;
 if ( error_code ) {
 info ( "%s: %s error %s " , __func__ , jobid2str ( job_ptr , jbuf , sizeof ( jbuf ) ) , slurm_strerror ( error_code ) ) ;
 }
 else {
 debug2 ( "%s: %s %s" , __func__ , jobid2str ( job_ptr , jbuf , sizeof ( jbuf ) ) , TIME_STR ) ;
 }
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 END_TIMER2 ( "_slurm_rpc_complete_job_allocation" ) ;
 if ( ( powercap_get_cluster_current_cap ( ) != 0 ) && ( which_power_layout ( ) == 2 ) ) {
 layouts_entity_pull_kv ( "power" , "Cluster" , "CurrentSumPower" ) ;
 }
 if ( error_code ) {
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 slurmctld_diag_stats . jobs_completed ++ ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 ( void ) schedule_job_save ( ) ;
 ( void ) schedule_node_save ( ) ;
 }
 trace_job ( job_ptr , __func__ , "return" ) ;
 }