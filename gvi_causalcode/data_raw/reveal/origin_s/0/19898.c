void proto_reg_handoff_ipmi_trace ( void ) {
 dissector_handle_t ipmi_trace_handle ;
 ipmi_trace_handle = create_dissector_handle ( dissect_ipmi_trace , proto_ipmi_trace ) ;
 dissector_add_uint ( "wtap_encap" , WTAP_ENCAP_IPMI_TRACE , ipmi_trace_handle ) ;
 dissector_add_uint ( "ipmi.protocol" , IPMI_PROTO_IPMB_1_0 , find_dissector ( "ipmb" ) ) ;
 dissector_add_uint ( "ipmi.protocol" , IPMI_PROTO_KCS , find_dissector ( "kcs" ) ) ;
 dissector_add_uint ( "ipmi.protocol" , IPMI_PROTO_TMODE , find_dissector ( "tmode" ) ) ;
 }