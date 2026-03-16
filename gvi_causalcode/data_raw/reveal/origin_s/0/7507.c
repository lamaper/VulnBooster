void proto_register_ipmi_trace ( void ) {
 proto_ipmi_trace = proto_register_protocol ( "IPMI Trace Data Collection" , "ipmi-trace" , "ipmi.trace" ) ;
 proto_register_field_array ( proto_ipmi_trace , ipmi_trace_hf , array_length ( ipmi_trace_hf ) ) ;
 proto_register_subtree_array ( ipmi_trace_ett , array_length ( ipmi_trace_ett ) ) ;
 proto_dissector_table = register_dissector_table ( "ipmi.protocol" , "IPMI Channel Protocol Type" , proto_ipmi_trace , FT_UINT8 , BASE_HEX , DISSECTOR_TABLE_NOT_ALLOW_DUPLICATE ) ;
 }