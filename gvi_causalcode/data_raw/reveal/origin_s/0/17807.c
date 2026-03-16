static int is_unvisited_pmns_names_frame ( packet_info * pinfo ) {
 pcp_conv_info_t * pcp_conv_info ;
 pcp_conv_info = get_pcp_conversation_info ( pinfo ) ;
 return pinfo -> num > pcp_conv_info -> last_processed_pmns_names_frame && pinfo -> num > pcp_conv_info -> last_pmns_names_frame ;
 }