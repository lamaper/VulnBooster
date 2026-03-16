inline static void _slurm_rpc_get_topo ( slurm_msg_t * msg ) {
 topo_info_response_msg_t * topo_resp_msg ;
 slurm_msg_t response_msg ;
 int i ;
 slurmctld_lock_t node_read_lock = {
 NO_LOCK , NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 DEF_TIMERS ;
 START_TIMER ;
 lock_slurmctld ( node_read_lock ) ;
 topo_resp_msg = xmalloc ( sizeof ( topo_info_response_msg_t ) ) ;
 topo_resp_msg -> record_count = switch_record_cnt ;
 topo_resp_msg -> topo_array = xmalloc ( sizeof ( topo_info_t ) * topo_resp_msg -> record_count ) ;
 for ( i = 0 ;
 i < topo_resp_msg -> record_count ;
 i ++ ) {
 topo_resp_msg -> topo_array [ i ] . level = switch_record_table [ i ] . level ;
 topo_resp_msg -> topo_array [ i ] . link_speed = switch_record_table [ i ] . link_speed ;
 topo_resp_msg -> topo_array [ i ] . name = xstrdup ( switch_record_table [ i ] . name ) ;
 topo_resp_msg -> topo_array [ i ] . nodes = xstrdup ( switch_record_table [ i ] . nodes ) ;
 topo_resp_msg -> topo_array [ i ] . switches = xstrdup ( switch_record_table [ i ] . switches ) ;
 }
 unlock_slurmctld ( node_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_get_topo" ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_TOPO_INFO ;
 response_msg . data = topo_resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 slurm_free_topo_info_msg ( topo_resp_msg ) ;
 }