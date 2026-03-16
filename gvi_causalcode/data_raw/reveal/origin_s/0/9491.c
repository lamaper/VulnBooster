void proto_reg_handoff_rtmpt ( void ) {
 dissector_handle_t amf_handle ;
 heur_dissector_add ( "tcp" , dissect_rtmpt_heur , "RTMPT over TCP" , "rtmpt_tcp" , proto_rtmpt , HEURISTIC_DISABLE ) ;
 rtmpt_tcp_handle = create_dissector_handle ( dissect_rtmpt_tcp , proto_rtmpt ) ;
 dissector_add_uint ( "tcp.port" , RTMP_PORT , rtmpt_tcp_handle ) ;
 rtmpt_http_handle = create_dissector_handle ( dissect_rtmpt_http , proto_rtmpt ) ;
 dissector_add_string ( "media_type" , "application/x-fcs" , rtmpt_http_handle ) ;
 amf_handle = create_dissector_handle ( dissect_amf , proto_amf ) ;
 dissector_add_string ( "media_type" , "application/x-amf" , amf_handle ) ;
 }