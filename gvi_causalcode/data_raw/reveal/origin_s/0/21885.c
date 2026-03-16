static void _slurm_rpc_dump_jobs_user ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump ;
 int dump_size ;
 slurm_msg_t response_msg ;
 job_user_id_msg_t * job_info_request_msg = ( job_user_id_msg_t * ) msg -> data ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , NO_LOCK , READ_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug3 ( "Processing RPC: REQUEST_JOB_USER_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 pack_all_jobs ( & dump , & dump_size , job_info_request_msg -> show_flags , uid , job_info_request_msg -> user_id , msg -> protocol_version ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_job_user" ) ;


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