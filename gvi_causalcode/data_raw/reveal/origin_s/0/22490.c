static void dissect_t38_udp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 guint8 octet1 ;
 proto_item * it ;
 proto_tree * tr ;
 guint32 offset = 0 ;
 if ( dissect_possible_rtpv2_packets_as_rtp ) {
 octet1 = tvb_get_guint8 ( tvb , offset ) ;
 if ( RTP_VERSION ( octet1 ) == 2 ) {
 call_dissector ( rtp_handle , tvb , pinfo , tree ) ;
 return ;
 }
 }
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "T.38" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 primary_part = TRUE ;
 Data_Field_item_num = 0 ;
 it = proto_tree_add_protocol_format ( tree , proto_t38 , tvb , 0 , - 1 , "ITU-T Recommendation T.38" ) ;
 tr = proto_item_add_subtree ( it , ett_t38 ) ;
 init_t38_info_conv ( pinfo ) ;
 if ( global_t38_show_setup_info ) {
 show_setup_info ( tvb , tr , p_t38_packet_conv ) ;
 }
 col_append_str ( pinfo -> cinfo , COL_INFO , "UDP: UDPTLPacket " ) ;
 offset = dissect_UDPTLPacket_PDU ( tvb , pinfo , tr , NULL ) ;
 if ( tvb_reported_length_remaining ( tvb , offset ) > 0 ) {
 proto_tree_add_expert_format ( tr , pinfo , & ei_t38_malformed , tvb , offset , tvb_reported_length_remaining ( tvb , offset ) , "[MALFORMED PACKET or wrong preference settings]" ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , " [Malformed?]" ) ;
 }
 }