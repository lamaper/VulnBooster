inline static void _slurm_rpc_dump_stats ( slurm_msg_t * msg ) {
 char * dump ;
 int dump_size ;
 stats_info_request_msg_t * request_msg ;
 slurm_msg_t response_msg ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 request_msg = ( stats_info_request_msg_t * ) msg -> data ;
 if ( ( request_msg -> command_id == STAT_COMMAND_RESET ) && ! validate_operator ( uid ) ) {
 error ( "Security violation: REQUEST_STATS_INFO reset " "from uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , ESLURM_ACCESS_DENIED ) ;
 return ;
 }
 debug2 ( "Processing RPC: REQUEST_STATS_INFO (command: %u)" , request_msg -> command_id ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_STATS_INFO ;
 if ( request_msg -> command_id == STAT_COMMAND_RESET ) {
 reset_stats ( 1 ) ;
 _clear_rpc_stats ( ) ;
 pack_all_stat ( 0 , & dump , & dump_size , msg -> protocol_version ) ;
 _pack_rpc_stats ( 0 , & dump , & dump_size , msg -> protocol_version ) ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 }
 else {
 pack_all_stat ( 1 , & dump , & dump_size , msg -> protocol_version ) ;
 _pack_rpc_stats ( 1 , & dump , & dump_size , msg -> protocol_version ) ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 }
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }