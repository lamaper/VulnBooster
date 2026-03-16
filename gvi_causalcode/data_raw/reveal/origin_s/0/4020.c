static int dissect_pbb_header ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , guint headerLength , guint tlvIndex ) {
 proto_tree * header_tree ;
 proto_tree * headerFlags_tree ;
 proto_item * header_item ;
 proto_item * headerFlags_item ;
 guint8 packet_flags = tvb_get_guint8 ( tvb , 0 ) ;
 header_item = proto_tree_add_item ( tree , hf_packetbb_header , tvb , 0 , headerLength , ENC_NA ) ;
 header_tree = proto_item_add_subtree ( header_item , ett_packetbb_header ) ;
 proto_tree_add_uint ( header_tree , hf_packetbb_version , tvb , 0 , 1 , packet_flags >> 4 ) ;
 headerFlags_item = proto_tree_add_item ( header_tree , hf_packetbb_header_flags , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 headerFlags_tree = proto_item_add_subtree ( headerFlags_item , ett_packetbb_header_flags ) ;
 proto_tree_add_item ( headerFlags_tree , hf_packetbb_header_flags_phasseqnum , tvb , 0 , 1 , ENC_NA ) ;
 proto_tree_add_item ( headerFlags_tree , hf_packetbb_header_flags_phastlv , tvb , 0 , 1 , ENC_NA ) ;
 if ( ( packet_flags & PACKET_HEADER_HASSEQNR ) != 0 ) {
 proto_tree_add_item ( header_tree , hf_packetbb_seqnr , tvb , 1 , 2 , ENC_BIG_ENDIAN ) ;
 }
 if ( ( packet_flags & PACKET_HEADER_HASTLV ) != 0 ) {
 return dissect_pbb_tlvblock ( tvb , pinfo , tree , tlvIndex , tvb_reported_length ( tvb ) , 0 , TLV_CAT_PACKET ) ;
 }
 return headerLength ;
 }