static int dissect_packetbb ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * ti ;
 proto_tree * packetbb_tree ;
 guint offset ;
 guint8 packet_flags ;
 guint headerLength = 1 ;
 guint tlvIndex = 0 ;
 packet_flags = tvb_get_guint8 ( tvb , 0 ) ;
 if ( ( packet_flags & PACKET_HEADER_HASSEQNR ) != 0 ) {
 headerLength += 2 ;
 }
 if ( ( packet_flags & PACKET_HEADER_HASTLV ) != 0 ) {
 tlvIndex = headerLength ;
 headerLength += 2 ;
 }
 if ( tvb_reported_length ( tvb ) < headerLength ) {
 return 0 ;
 }
 if ( ( packet_flags & PACKET_HEADER_HASTLV ) != 0 ) {
 headerLength += tvb_get_ntohs ( tvb , tlvIndex ) ;
 }
 if ( tvb_reported_length ( tvb ) < headerLength ) {
 return 0 ;
 }
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "packetbb" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 ti = proto_tree_add_item ( tree , proto_packetbb , tvb , 0 , - 1 , ENC_NA ) ;
 packetbb_tree = proto_item_add_subtree ( ti , ett_packetbb ) ;
 offset = dissect_pbb_header ( tvb , pinfo , packetbb_tree , headerLength , tlvIndex ) ;
 while ( offset < tvb_reported_length ( tvb ) ) {
 offset = dissect_pbb_message ( tvb , pinfo , packetbb_tree , offset ) ;
 }
 return tvb_captured_length ( tvb ) ;
 }