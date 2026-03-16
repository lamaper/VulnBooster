inline static void _slurm_rpc_reboot_nodes ( slurm_msg_t * msg ) {
 int rc ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;

 struct node_record * node_ptr ;
 reboot_msg_t * reboot_msg = ( reboot_msg_t * ) msg -> data ;
 char * nodelist = NULL ;
 bitstr_t * bitmap = NULL ;
 slurmctld_lock_t node_write_lock = {
 NO_LOCK , NO_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 time_t now = time ( NULL ) ;

 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_REBOOT_NODES from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Security violation, REBOOT_NODES RPC from uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , EACCES ) ;
 return ;
 }


 if ( ! nodelist || ! xstrcasecmp ( nodelist , "ALL" ) ) {
 bitmap = bit_alloc ( node_record_count ) ;
 bit_nset ( bitmap , 0 , ( node_record_count - 1 ) ) ;
 }
 else if ( node_name2bitmap ( nodelist , false , & bitmap ) != 0 ) {
 FREE_NULL_BITMAP ( bitmap ) ;
 error ( "Bad node list in REBOOT_NODES request: %s" , nodelist ) ;
 slurm_send_rc_msg ( msg , ESLURM_INVALID_NODE_NAME ) ;
 return ;
 }
 lock_slurmctld ( node_write_lock ) ;
 for ( i = 0 , node_ptr = node_record_table_ptr ;
 i < node_record_count ;
 i ++ , node_ptr ++ ) {
 if ( ! bit_test ( bitmap , i ) ) continue ;
 if ( IS_NODE_FUTURE ( node_ptr ) || IS_NODE_DOWN ( node_ptr ) || ( IS_NODE_CLOUD ( node_ptr ) && IS_NODE_POWER_SAVE ( node_ptr ) ) ) {
 bit_clear ( bitmap , i ) ;
 continue ;
 }
 node_ptr -> node_state |= NODE_STATE_REBOOT ;
 node_ptr -> boot_req_time = now ;
 node_ptr -> last_response = now + slurmctld_config . boot_time ;
 if ( reboot_msg && ( reboot_msg -> flags & REBOOT_FLAGS_ASAP ) ) {
 node_ptr -> node_state |= NODE_STATE_DRAIN ;
 if ( node_ptr -> reason == NULL ) {
 node_ptr -> reason = xstrdup ( "Reboot ASAP" ) ;
 node_ptr -> reason_time = now ;
 node_ptr -> reason_uid = uid ;
 }
 }
 want_nodes_reboot = true ;
 }
 if ( want_nodes_reboot == true ) schedule_node_save ( ) ;
 unlock_slurmctld ( node_write_lock ) ;
 if ( want_nodes_reboot == true ) {
 nodelist = bitmap2node_name ( bitmap ) ;
 info ( "reboot request queued for nodes %s" , nodelist ) ;
 xfree ( nodelist ) ;
 }
 FREE_NULL_BITMAP ( bitmap ) ;
 rc = SLURM_SUCCESS ;

 slurm_send_rc_msg ( msg , rc ) ;
 }