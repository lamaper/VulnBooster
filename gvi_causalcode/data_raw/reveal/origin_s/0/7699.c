static void _slurm_rpc_composite_msg ( slurm_msg_t * msg ) {
 static time_t config_update = 0 ;
 static bool defer_sched = false ;
 static int sched_timeout = 0 ;
 static int active_rpc_cnt = 0 ;
 struct timeval start_tv ;
 bool run_scheduler = false ;
 composite_msg_t * comp_msg , comp_resp_msg ;
 slurmctld_lock_t job_write_lock = {
 READ_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 memset ( & comp_resp_msg , 0 , sizeof ( composite_msg_t ) ) ;
 comp_resp_msg . msg_list = list_create ( _slurmctld_free_comp_msg_list ) ;
 comp_msg = ( composite_msg_t * ) msg -> data ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_ROUTE ) info ( "Processing RPC: MESSAGE_COMPOSITE msg with %d messages" , comp_msg -> msg_list ? list_count ( comp_msg -> msg_list ) : 0 ) ;
 if ( config_update != slurmctld_conf . last_update ) {
 char * sched_params = slurm_get_sched_params ( ) ;
 int time_limit ;
 char * tmp_ptr ;
 defer_sched = ( sched_params && strstr ( sched_params , "defer" ) ) ;
 time_limit = slurm_get_msg_timeout ( ) / 2 ;
 if ( sched_params && ( tmp_ptr = strstr ( sched_params , "max_sched_time=" ) ) ) {
 sched_timeout = atoi ( tmp_ptr + 15 ) ;
 if ( ( sched_timeout <= 0 ) || ( sched_timeout > time_limit ) ) {
 error ( "Invalid max_sched_time: %d" , sched_timeout ) ;
 sched_timeout = 0 ;
 }
 }
 if ( sched_timeout == 0 ) {
 sched_timeout = MAX ( time_limit , 1 ) ;
 sched_timeout = MIN ( sched_timeout , 2 ) ;
 sched_timeout *= 1000000 ;
 }
 xfree ( sched_params ) ;
 config_update = slurmctld_conf . last_update ;
 }
 _throttle_start ( & active_rpc_cnt ) ;
 lock_slurmctld ( job_write_lock ) ;
 gettimeofday ( & start_tv , NULL ) ;
 _slurm_rpc_comp_msg_list ( comp_msg , & run_scheduler , comp_resp_msg . msg_list , & start_tv , sched_timeout ) ;
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 if ( list_count ( comp_resp_msg . msg_list ) ) {
 slurm_msg_t resp_msg ;
 slurm_msg_t_init ( & resp_msg ) ;
 resp_msg . flags = msg -> flags ;
 resp_msg . protocol_version = msg -> protocol_version ;
 memcpy ( & resp_msg . address , & comp_msg -> sender , sizeof ( slurm_addr_t ) ) ;
 resp_msg . msg_type = RESPONSE_MESSAGE_COMPOSITE ;
 resp_msg . data = & comp_resp_msg ;
 slurm_send_only_node_msg ( & resp_msg ) ;
 }
 FREE_NULL_LIST ( comp_resp_msg . msg_list ) ;
 if ( run_scheduler ) {
 if ( ! LOTS_OF_AGENTS && ! defer_sched ) ( void ) schedule ( 0 ) ;
 schedule_node_save ( ) ;
 schedule_job_save ( ) ;
 }
 }