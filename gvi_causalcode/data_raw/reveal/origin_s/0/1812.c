inline static void _slurm_rpc_dump_licenses ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump ;
 int dump_size ;
 slurm_msg_t response_msg ;
 license_info_request_msg_t * lic_req_msg ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "%s: Processing RPC: REQUEST_LICENSE_INFO uid=%d" , __func__ , uid ) ;
 lic_req_msg = ( license_info_request_msg_t * ) msg -> data ;
 if ( ( lic_req_msg -> last_update - 1 ) >= last_license_update ) {
 debug2 ( "%s: no change SLURM_NO_CHANGE_IN_DATA" , __func__ ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 return ;
 }
 get_all_license_info ( & dump , & dump_size , uid , msg -> protocol_version ) ;
 END_TIMER2 ( "_slurm_rpc_dump_licenses" ) ;
 debug2 ( "%s: size=%d %s" , __func__ , dump_size , TIME_STR ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_LICENSE_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }