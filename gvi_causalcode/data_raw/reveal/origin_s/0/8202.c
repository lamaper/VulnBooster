void proto_reg_handoff_steam_ihs_discovery ( void ) {
 static gboolean initialized = FALSE ;
 static dissector_handle_t steam_ihs_discovery_handle ;
 static int current_port ;
 if ( ! initialized ) {
 steam_ihs_discovery_handle = create_dissector_handle ( dissect_steam_ihs_discovery , proto_steam_ihs_discovery ) ;
 initialized = TRUE ;
 }
 else {
 dissector_delete_uint ( "udp.port" , current_port , steam_ihs_discovery_handle ) ;
 }
 current_port = udp_port_pref ;
 dissector_add_uint ( "udp.port" , current_port , steam_ihs_discovery_handle ) ;
 }