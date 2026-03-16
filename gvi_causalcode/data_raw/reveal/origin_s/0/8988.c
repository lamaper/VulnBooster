void proto_reg_handoff_opcua ( void ) {
 opcua_handle = create_dissector_handle ( dissect_opcua , proto_opcua ) ;
 dissector_add_uint_range_with_preference ( "tcp.port" , OPCUA_PORT_RANGE , opcua_handle ) ;
 }