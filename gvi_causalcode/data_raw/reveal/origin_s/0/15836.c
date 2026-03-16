static void _proc_multi_msg ( uint32_t rpc_uid , slurm_msg_t * msg ) {
 slurm_msg_t sub_msg , response_msg ;
 ctld_list_msg_t * ctld_req_msg , ctld_resp_msg ;
 List full_resp_list = NULL ;
 Buf single_req_buf = NULL ;
 Buf ret_buf , resp_buf = NULL ;
 ListIterator iter = NULL ;
 int rc ;
 if ( ! msg -> conn ) {
 error ( "Security violation, REQUEST_CTLD_MULT_MSG RPC from uid=%d" , rpc_uid ) ;
 slurm_send_rc_msg ( msg , ESLURM_ACCESS_DENIED ) ;
 return ;
 }
 ctld_req_msg = ( ctld_list_msg_t * ) msg -> data ;
 full_resp_list = list_create ( _ctld_free_list_msg ) ;
 iter = list_iterator_create ( ctld_req_msg -> my_list ) ;
 while ( ( single_req_buf = list_next ( iter ) ) ) {
 slurm_msg_t_init ( & sub_msg ) ;
 if ( unpack16 ( & sub_msg . msg_type , single_req_buf ) || unpack_msg ( & sub_msg , single_req_buf ) ) {
 error ( "Sub-message unpack error for REQUEST_CTLD_MULT_MSG %u RPC" , sub_msg . msg_type ) ;
 ret_buf = _build_rc_buf ( SLURM_ERROR , msg -> protocol_version ) ;
 list_append ( full_resp_list , ret_buf ) ;
 continue ;
 }
 sub_msg . conn = msg -> conn ;
 sub_msg . auth_cred = msg -> auth_cred ;
 ret_buf = NULL ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_PROTOCOL ) {
 char * p = rpc_num2string ( sub_msg . msg_type ) ;
 info ( "%s: received opcode %s" , __func__ , p ) ;
 }
 switch ( sub_msg . msg_type ) {
 case REQUEST_PING : rc = SLURM_SUCCESS ;
 ret_buf = _build_rc_buf ( rc , msg -> protocol_version ) ;
 break ;
 case REQUEST_SIB_MSG : _slurm_rpc_sib_msg ( rpc_uid , & sub_msg ) ;
 ret_buf = _build_rc_buf ( SLURM_SUCCESS , msg -> protocol_version ) ;
 break ;
 default : error ( "%s: Unsupported Message Type:%s" , __func__ , rpc_num2string ( sub_msg . msg_type ) ) ;
 }
 ( void ) slurm_free_msg_data ( sub_msg . msg_type , sub_msg . data ) ;
 if ( ! ret_buf ) {
 ret_buf = _build_rc_buf ( SLURM_ERROR , msg -> protocol_version ) ;
 }
 list_append ( full_resp_list , ret_buf ) ;
 }
 list_iterator_destroy ( iter ) ;
 ctld_resp_msg . my_list = full_resp_list ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_CTLD_MULT_MSG ;
 response_msg . data = & ctld_resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 FREE_NULL_LIST ( full_resp_list ) ;
 free_buf ( resp_buf ) ;
 return ;
 }