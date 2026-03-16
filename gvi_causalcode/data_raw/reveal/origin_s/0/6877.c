inline static void _slurm_rpc_get_powercap ( slurm_msg_t * msg ) {
 powercap_info_msg_t * powercap_resp_msg , * ptr ;
 slurm_msg_t response_msg ;
 slurmctld_lock_t config_read_lock = {
 READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 DEF_TIMERS ;
 START_TIMER ;
 lock_slurmctld ( config_read_lock ) ;
 powercap_resp_msg = xmalloc ( sizeof ( powercap_info_msg_t ) ) ;
 ptr = powercap_resp_msg ;
 ptr -> power_cap = powercap_get_cluster_current_cap ( ) ;
 ptr -> min_watts = powercap_get_cluster_min_watts ( ) ;
 ptr -> cur_max_watts = powercap_get_cluster_current_max_watts ( ) ;
 ptr -> adj_max_watts = powercap_get_cluster_adjusted_max_watts ( ) ;
 ptr -> max_watts = powercap_get_cluster_max_watts ( ) ;
 unlock_slurmctld ( config_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_get_powercap" ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_POWERCAP_INFO ;
 response_msg . data = powercap_resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 slurm_free_powercap_info_msg ( powercap_resp_msg ) ;
 }