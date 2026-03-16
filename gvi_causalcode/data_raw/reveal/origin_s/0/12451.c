static void _slurm_rpc_layout_show ( slurm_msg_t * msg ) {
 layout_info_request_msg_t * layout_req_msg = ( layout_info_request_msg_t * ) msg -> data ;
 DEF_TIMERS ;
 slurm_msg_t response_msg ;
 char * dump ;
 int dump_size ;
 static int high_buffer_size = ( 1024 * 1024 ) ;
 Buf buffer = init_buf ( high_buffer_size ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_LAYOUT_INFO" ) ;
 if ( layout_req_msg -> layout_type == NULL ) {
 dump = slurm_get_layouts ( ) ;
 pack32 ( ( uint32_t ) 2 , buffer ) ;
 packstr ( dump , buffer ) ;
 packstr ( "\n" , buffer ) ;
 xfree ( dump ) ;
 }
 else {
 if ( layouts_pack_layout ( layout_req_msg -> layout_type , layout_req_msg -> entities , layout_req_msg -> type , layout_req_msg -> flags , buffer ) != SLURM_SUCCESS ) {
 debug2 ( "%s: unable to get layout[%s]" , __func__ , layout_req_msg -> layout_type ) ;
 slurm_send_rc_msg ( msg , SLURM_NO_CHANGE_IN_DATA ) ;
 free_buf ( buffer ) ;
 return ;
 }
 }
 dump_size = get_buf_offset ( buffer ) ;
 high_buffer_size = MAX ( high_buffer_size , dump_size ) ;
 dump = xfer_buf_data ( buffer ) ;
 END_TIMER2 ( "_slurm_rpc_resv_show" ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . address = msg -> address ;
 response_msg . conn = msg -> conn ;
 response_msg . msg_type = RESPONSE_LAYOUT_INFO ;
 response_msg . data = dump ;
 response_msg . data_size = dump_size ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( dump ) ;
 }