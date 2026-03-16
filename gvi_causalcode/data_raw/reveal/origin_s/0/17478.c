void proto_reg_handoff_h245 ( void ) {
 dissector_handle_t h245_handle ;
 rtcp_handle = find_dissector ( "rtcp" ) ;
 data_handle = find_dissector ( "data" ) ;
 h263_handle = find_dissector ( "h263data" ) ;
 amr_handle = find_dissector ( "amr_if2_nb" ) ;
 h245_handle = find_dissector ( "h245" ) ;
 dissector_add_handle ( "tcp.port" , h245_handle ) ;
 MultimediaSystemControlMessage_handle = find_dissector ( "h245dg" ) ;
 dissector_add_handle ( "udp.port" , MultimediaSystemControlMessage_handle ) ;
 }