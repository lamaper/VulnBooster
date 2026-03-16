void proto_reg_handoff_t38 ( void ) {
 static gboolean t38_prefs_initialized = FALSE ;
 static guint tcp_port ;
 static guint udp_port ;
 if ( ! t38_prefs_initialized ) {
 t38_udp_handle = create_dissector_handle ( dissect_t38_udp , proto_t38 ) ;
 t38_tcp_handle = create_dissector_handle ( dissect_t38_tcp , proto_t38 ) ;
 t38_tcp_pdu_handle = create_dissector_handle ( dissect_t38_tcp_pdu , proto_t38 ) ;
 rtp_handle = find_dissector ( "rtp" ) ;
 t30_hdlc_handle = find_dissector ( "t30.hdlc" ) ;
 data_handle = find_dissector ( "data" ) ;
 t38_prefs_initialized = TRUE ;
 }
 else {
 dissector_delete_uint ( "tcp.port" , tcp_port , t38_tcp_handle ) ;
 dissector_delete_uint ( "udp.port" , udp_port , t38_udp_handle ) ;
 }
 tcp_port = global_t38_tcp_port ;
 udp_port = global_t38_udp_port ;
 dissector_add_uint ( "tcp.port" , tcp_port , t38_tcp_handle ) ;
 dissector_add_uint ( "udp.port" , udp_port , t38_udp_handle ) ;
 }