void proto_reg_handoff_netbios ( void ) {
 dissector_handle_t netbios_handle ;
 netbios_handle = create_dissector_handle ( dissect_netbios , proto_netbios ) ;
 dissector_add_uint ( "llc.dsap" , SAP_NETBIOS , netbios_handle ) ;
 register_capture_dissector ( "llc.dsap" , SAP_NETBIOS , capture_netbios , proto_netbios ) ;
 }