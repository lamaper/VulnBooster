static void _slurm_rpc_dump_front_end ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump = NULL ;
 int dump_size = 0 ;
 slurm_msg_t response_msg ;
 front_end_info_request_msg_t * front_end_req_msg = ( front_end_info_request_msg_t * ) msg -> data ;
 slurmctld_lock_t node_read_lock = {
 READ_LOCK , NO_LOCK , NO_LOCK , READ_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug3 ( "Processing RPC: REQUEST_FRONT_END_INFO from uid=%d" , uid ) ;
 lock_slurmctld ( node_read_lock ) ;
 if ( ( front_end_req_msg -> last_update - 1 ) >= last_front_end_update ) {
 unlock_slurmctld ( node_read_lock ) ;
 debug3 ( "_slurm_rpc_dump_front_end, no change" ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 }
 else {
 pack_all_front_end ( & dump , & dump_size , uid , msg -> protocol_version ) ;
 unlock_slurmctld ( node_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_front_end" ) ;
 debug2 ( "_slurm_rpc_dump_front_end, size=%d %s" , dump_size , TIME_STR ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_FRONT_END_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }
 }