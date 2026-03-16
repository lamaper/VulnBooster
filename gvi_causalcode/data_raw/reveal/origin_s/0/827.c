void proto_reg_handoff_packetbb ( void ) {
 static gboolean packetbb_prefs_initialized = FALSE ;
 static dissector_handle_t packetbb_handle ;
 static guint packetbb_udp_port ;
 if ( ! packetbb_prefs_initialized ) {
 packetbb_handle = create_dissector_handle ( dissect_packetbb , proto_packetbb ) ;
 packetbb_prefs_initialized = TRUE ;
 }
 else {
 dissector_delete_uint ( "udp.port" , global_packetbb_port , packetbb_handle ) ;
 }
 packetbb_udp_port = global_packetbb_port ;
 dissector_add_uint ( "udp.port" , packetbb_udp_port , packetbb_handle ) ;
 }