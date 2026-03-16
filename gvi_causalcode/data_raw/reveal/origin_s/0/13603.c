void t38_add_address ( packet_info * pinfo , address * addr , int port , int other_port , const gchar * setup_method , guint32 setup_frame_number ) {
 address null_addr ;
 conversation_t * p_conversation ;
 t38_conv * p_conversation_data = NULL ;
 if ( ( pinfo -> fd -> flags . visited ) || ( t38_udp_handle == NULL ) ) {
 return ;
 }
 SET_ADDRESS ( & null_addr , AT_NONE , 0 , NULL ) ;
 p_conversation = find_conversation ( setup_frame_number , addr , & null_addr , PT_UDP , port , other_port , NO_ADDR_B | ( ! other_port ? NO_PORT_B : 0 ) ) ;
 if ( ! p_conversation || p_conversation -> setup_frame != setup_frame_number ) {
 p_conversation = conversation_new ( setup_frame_number , addr , & null_addr , PT_UDP , ( guint32 ) port , ( guint32 ) other_port , NO_ADDR2 | ( ! other_port ? NO_PORT2 : 0 ) ) ;
 }
 conversation_set_dissector ( p_conversation , t38_udp_handle ) ;
 p_conversation_data = ( t38_conv * ) conversation_get_proto_data ( p_conversation , proto_t38 ) ;
 if ( ! p_conversation_data ) {
 p_conversation_data = wmem_new ( wmem_file_scope ( ) , t38_conv ) ;
 conversation_add_proto_data ( p_conversation , proto_t38 , p_conversation_data ) ;
 }
 g_strlcpy ( p_conversation_data -> setup_method , setup_method , MAX_T38_SETUP_METHOD_SIZE ) ;
 p_conversation_data -> setup_frame_number = setup_frame_number ;
 p_conversation_data -> src_t38_info . reass_ID = 0 ;
 p_conversation_data -> src_t38_info . reass_start_seqnum = - 1 ;
 p_conversation_data -> src_t38_info . reass_data_type = 0 ;
 p_conversation_data -> src_t38_info . last_seqnum = - 1 ;
 p_conversation_data -> src_t38_info . packet_lost = 0 ;
 p_conversation_data -> src_t38_info . burst_lost = 0 ;
 p_conversation_data -> src_t38_info . time_first_t4_data = 0 ;
 p_conversation_data -> src_t38_info . additional_hdlc_data_field_counter = 0 ;
 p_conversation_data -> src_t38_info . seqnum_prev_data_field = - 1 ;
 p_conversation_data -> dst_t38_info . reass_ID = 0 ;
 p_conversation_data -> dst_t38_info . reass_start_seqnum = - 1 ;
 p_conversation_data -> dst_t38_info . reass_data_type = 0 ;
 p_conversation_data -> dst_t38_info . last_seqnum = - 1 ;
 p_conversation_data -> dst_t38_info . packet_lost = 0 ;
 p_conversation_data -> dst_t38_info . burst_lost = 0 ;
 p_conversation_data -> dst_t38_info . time_first_t4_data = 0 ;
 p_conversation_data -> dst_t38_info . additional_hdlc_data_field_counter = 0 ;
 p_conversation_data -> dst_t38_info . seqnum_prev_data_field = - 1 ;
 }