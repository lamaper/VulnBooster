void proto_reg_handoff_applemidi ( void ) {
 applemidi_handle = create_dissector_handle ( dissect_applemidi , proto_applemidi ) ;
 rtp_handle = find_dissector ( "rtp" ) ;
 heur_dissector_add ( "udp" , dissect_applemidi_heur , proto_applemidi ) ;
 }