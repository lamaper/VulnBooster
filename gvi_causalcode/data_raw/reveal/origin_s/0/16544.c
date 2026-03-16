static void _slurm_rpc_dump_job_single ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump = NULL ;
 int dump_size , rc ;
 slurm_msg_t response_msg ;
 job_id_msg_t * job_id_msg = ( job_id_msg_t * ) msg -> data ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , NO_LOCK , READ_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug3 ( "Processing RPC: REQUEST_JOB_INFO_SINGLE from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 rc = pack_one_job ( & dump , & dump_size , job_id_msg -> job_id , job_id_msg -> show_flags , uid , msg -> protocol_version ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_job_single" ) ;


 slurm_send_rc_msg ( msg , rc ) ;
 }
 else {
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_JOB_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 }
 xfree ( dump ) ;
 }