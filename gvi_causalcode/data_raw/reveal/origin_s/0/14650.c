void proto_reg_handoff_iax2 ( void ) {
 dissector_handle_t v110_handle ;
 dissector_add_uint ( "udp.port" , IAX2_PORT , find_dissector ( "iax2" ) ) ;
 v110_handle = find_dissector ( "v110" ) ;
 if ( v110_handle ) dissector_add_uint ( "iax2.dataformat" , AST_DATAFORMAT_V110 , v110_handle ) ;
 data_handle = find_dissector ( "data" ) ;
 }