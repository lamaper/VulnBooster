static void _slurm_rpc_dump_partitions ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 char * dump ;
 int dump_size ;
 slurm_msg_t response_msg ;
 part_info_request_msg_t * part_req_msg ;
 slurmctld_lock_t part_read_lock = {
 READ_LOCK , NO_LOCK , NO_LOCK , READ_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_PARTITION_INFO uid=%d" , uid ) ;
 part_req_msg = ( part_info_request_msg_t * ) msg -> data ;
 lock_slurmctld ( part_read_lock ) ;
 if ( ( slurmctld_conf . private_data & PRIVATE_DATA_PARTITIONS ) && ! validate_operator ( uid ) ) {
 unlock_slurmctld ( part_read_lock ) ;
 debug2 ( "Security violation, PARTITION_INFO RPC from uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , ESLURM_ACCESS_DENIED ) ;
 }
 else if ( ( part_req_msg -> last_update - 1 ) >= last_part_update ) {
 unlock_slurmctld ( part_read_lock ) ;
 debug2 ( "_slurm_rpc_dump_partitions, no change" ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 }
 else {
 pack_all_part ( & dump , & dump_size , part_req_msg -> show_flags , uid , msg -> protocol_version ) ;
 unlock_slurmctld ( part_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_dump_partitions" ) ;
 debug2 ( "_slurm_rpc_dump_partitions, size=%d %s" , dump_size , TIME_STR ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_PARTITION_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }
 }