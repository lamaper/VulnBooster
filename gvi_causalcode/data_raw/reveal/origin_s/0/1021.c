void proto_reg_handoff_pkt_ccc ( void ) {
 static gboolean initialized = FALSE ;
 static dissector_handle_t pkt_ccc_handle ;
 static guint saved_pkt_ccc_udp_port ;
 if ( ! initialized ) {
 pkt_ccc_handle = find_dissector ( "pkt_ccc" ) ;
 dissector_add_handle ( "udp.port" , pkt_ccc_handle ) ;
 initialized = TRUE ;
 }
 else {
 if ( saved_pkt_ccc_udp_port != 0 ) {
 dissector_delete_uint ( "udp.port" , saved_pkt_ccc_udp_port , pkt_ccc_handle ) ;
 }
 }
 if ( global_pkt_ccc_udp_port != 0 ) {
 dissector_add_uint ( "udp.port" , global_pkt_ccc_udp_port , pkt_ccc_handle ) ;
 }
 saved_pkt_ccc_udp_port = global_pkt_ccc_udp_port ;
 }