static void _slurm_rpc_comp_msg_list ( composite_msg_t * comp_msg , bool * run_scheduler , List msg_list_in , struct timeval * start_tv , int timeout ) {
 ListIterator itr ;
 slurm_msg_t * next_msg ;
 composite_msg_t * ncomp_msg ;
 composite_msg_t * comp_resp_msg ;
 slurmctld_lock_t job_write_lock = {
 READ_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 DEF_TIMERS ;
 START_TIMER ;
 itr = list_iterator_create ( comp_msg -> msg_list ) ;
 while ( ( next_msg = list_next ( itr ) ) ) {
 if ( slurm_delta_tv ( start_tv ) >= timeout ) {
 END_TIMER ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_ROUTE ) info ( "composite message processing " "yielding locks after running for %s" , TIME_STR ) ;
 unlock_slurmctld ( job_write_lock ) ;
 usleep ( 10 ) ;
 lock_slurmctld ( job_write_lock ) ;
 gettimeofday ( start_tv , NULL ) ;
 START_TIMER ;
 }
 FREE_NULL_LIST ( next_msg -> ret_list ) ;
 next_msg -> ret_list = msg_list_in ;
 switch ( next_msg -> msg_type ) {
 case MESSAGE_COMPOSITE : comp_resp_msg = xmalloc ( sizeof ( composite_msg_t ) ) ;
 comp_resp_msg -> msg_list = list_create ( _slurmctld_free_comp_msg_list ) ;
 ncomp_msg = ( composite_msg_t * ) next_msg -> data ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_ROUTE ) info ( "Processing embedded MESSAGE_COMPOSITE " "msg with %d direct " "messages" , ncomp_msg -> msg_list ? list_count ( ncomp_msg -> msg_list ) : 0 ) ;
 _slurm_rpc_comp_msg_list ( ncomp_msg , run_scheduler , comp_resp_msg -> msg_list , start_tv , timeout ) ;
 if ( list_count ( comp_resp_msg -> msg_list ) ) {
 slurm_msg_t * resp_msg = xmalloc_nz ( sizeof ( slurm_msg_t ) ) ;
 slurm_msg_t_init ( resp_msg ) ;
 resp_msg -> msg_index = next_msg -> msg_index ;
 resp_msg -> flags = next_msg -> flags ;
 resp_msg -> protocol_version = next_msg -> protocol_version ;
 resp_msg -> msg_type = RESPONSE_MESSAGE_COMPOSITE ;
 memcpy ( & comp_resp_msg -> sender , & ncomp_msg -> sender , sizeof ( slurm_addr_t ) ) ;
 resp_msg -> data = comp_resp_msg ;
 list_append ( msg_list_in , resp_msg ) ;
 }
 else slurm_free_composite_msg ( comp_resp_msg ) ;
 break ;
 case REQUEST_COMPLETE_BATCH_SCRIPT : case REQUEST_COMPLETE_BATCH_JOB : _slurm_rpc_complete_batch_script ( next_msg , run_scheduler , 1 ) ;
 break ;
 case REQUEST_STEP_COMPLETE : _slurm_rpc_step_complete ( next_msg , 1 ) ;
 break ;
 case MESSAGE_EPILOG_COMPLETE : _slurm_rpc_epilog_complete ( next_msg , run_scheduler , 1 ) ;
 break ;
 case MESSAGE_NODE_REGISTRATION_STATUS : _slurm_rpc_node_registration ( next_msg , 1 ) ;
 break ;
 default : error ( "_slurm_rpc_comp_msg_list: invalid msg type" ) ;
 break ;
 }
 next_msg -> ret_list = NULL ;
 }
 list_iterator_destroy ( itr ) ;
 END_TIMER ;
 }