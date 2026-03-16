void proto_reg_handoff_coap ( void ) {
 media_type_dissector_table = find_dissector_table ( "media_type" ) ;
 dissector_add_uint_with_preference ( "udp.port" , DEFAULT_COAP_PORT , coap_handle ) ;
 dtls_dissector_add ( DEFAULT_COAPS_PORT , coap_handle ) ;
 oscore_handle = find_dissector ( "oscore" ) ;
 }