static void _slurm_rpc_dump_jobs ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump ;
 int dump_size ;
 slurm_msg_t response_msg ;
 job_info_request_msg_t * job_info_request_msg = ( job_info_request_msg_t * ) msg -> data ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , NO_LOCK , READ_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug3 ( "Processing RPC: REQUEST_JOB_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 if ( ( job_info_request_msg -> last_update - 1 ) >= last_job_update ) {
 unlock_slurmctld ( job_read_lock ) ;
 debug3 ( "_slurm_rpc_dump_jobs, no change" ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 }
 else {
 if ( job_info_request_msg -> job_ids ) {
 pack_spec_jobs ( & dump , & dump_size , job_info_request_msg -> job_ids , job_info_request_msg -> show_flags , uid , NO_VAL , msg -> protocol_version ) ;
 }
 else {
 pack_all_jobs ( & dump , & dump_size , job_info_request_msg -> show_flags , uid , NO_VAL , msg -> protocol_version ) ;
 }
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_jobs" ) ;


 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_JOB_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }
 }