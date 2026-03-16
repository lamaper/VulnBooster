void proto_reg_handoff_h225 ( void ) {
 static gboolean h225_prefs_initialized = FALSE ;
 static dissector_handle_t q931_tpkt_handle ;
 static guint saved_h225_tls_port ;
 if ( ! h225_prefs_initialized ) {
 dissector_add_uint ( "udp.port" , UDP_PORT_RAS1 , h225ras_handle ) ;
 dissector_add_uint ( "udp.port" , UDP_PORT_RAS2 , h225ras_handle ) ;
 h245_handle = find_dissector ( "h245" ) ;
 h245dg_handle = find_dissector ( "h245dg" ) ;
 h4501_handle = find_dissector ( "h4501" ) ;
 data_handle = find_dissector ( "data" ) ;
 h225_prefs_initialized = TRUE ;
 q931_tpkt_handle = find_dissector ( "q931.tpkt" ) ;
 }
 else {
 ssl_dissector_delete ( saved_h225_tls_port , q931_tpkt_handle ) ;
 }
 saved_h225_tls_port = h225_tls_port ;
 ssl_dissector_add ( saved_h225_tls_port , q931_tpkt_handle ) ;
 }