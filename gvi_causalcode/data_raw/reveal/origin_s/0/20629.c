static pcp_conv_info_t * get_pcp_conversation_info ( packet_info * pinfo ) {
 conversation_t * conversation ;
 pcp_conv_info_t * pcp_conv_info ;
 conversation = find_conversation ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , pinfo -> srcport , pinfo -> destport , 0 ) ;
 DISSECTOR_ASSERT ( conversation ) ;
 pcp_conv_info = ( pcp_conv_info_t * ) conversation_get_proto_data ( conversation , proto_pcp ) ;
 DISSECTOR_ASSERT ( pcp_conv_info ) ;
 return pcp_conv_info ;
 }