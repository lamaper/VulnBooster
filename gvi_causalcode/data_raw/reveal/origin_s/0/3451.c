void proto_reg_handoff_q931 ( void ) {
 dissector_add_uint ( "lapd.sapi" , LAPD_SAPI_Q931 , q931_handle ) ;
 dissector_add_uint ( "sctp.ppi" , H323_PAYLOAD_PROTOCOL_ID , q931_over_ip_handle ) ;
 dissector_add_uint ( "osinl.incl" , NLPID_Q_931 , q931_handle ) ;
 h225_handle = find_dissector_add_dependency ( "h225" , proto_q931 ) ;
 heur_dissector_add ( "tcp" , dissect_q931_tpkt_heur , "Q.931 over TPKT over TCP" , "q931_tcp" , proto_q931 , HEURISTIC_ENABLE ) ;
 }