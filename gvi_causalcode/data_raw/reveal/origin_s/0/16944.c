static void _slurm_rpc_resv_show ( slurm_msg_t * msg ) {
 resv_info_request_msg_t * resv_req_msg = ( resv_info_request_msg_t * ) msg -> data ;
 DEF_TIMERS ;
 slurmctld_lock_t node_read_lock = {
 NO_LOCK , NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurm_msg_t response_msg ;
 char * dump ;
 int dump_size ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_RESERVATION_INFO from uid=%d" , uid ) ;
 if ( ( resv_req_msg -> last_update - 1 ) >= last_resv_update ) {
 debug2 ( "_slurm_rpc_resv_show, no change" ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 }
 else {
 lock_slurmctld ( node_read_lock ) ;
 show_resv ( & dump , & dump_size , uid , msg -> protocol_version ) ;
 unlock_slurmctld ( node_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_resv_show" ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_RESERVATION_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }
 }