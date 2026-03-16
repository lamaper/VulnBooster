static void dissect_rsvp_eth_tspec_tlv ( proto_item * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int tlv_length , int subtree_type ) {
 int tlv_off ;
 int bit_offset ;
 guint16 tlv_type ;
 int tlv_len ;
 guint8 profile ;
 proto_tree * rsvp_ethspec_subtree , * ethspec_profile_subtree , * ti3 ;
 for ( tlv_off = 0 ;
 tlv_off < tlv_length ;
 ) {
 tlv_type = tvb_get_ntohs ( tvb , offset + tlv_off ) ;
 tlv_len = tvb_get_ntohs ( tvb , offset + tlv_off + 2 ) ;
 if ( ( tlv_len == 0 ) || ( tlv_off + tlv_len > tlv_length ) ) {
 proto_tree_add_expert ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset + tlv_off + 2 , 2 ) ;
 return ;
 }
 switch ( tlv_type ) {
 case 0 : case 1 : case 2 : rsvp_ethspec_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + tlv_off , tlv_len , subtree_type , NULL , "Ethernet Bandwidth Profile TLV: CIR=%.10g, CBS=%.10g, " "EIR=%.10g, EBS=%.10g" , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 8 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 12 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 16 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 20 ) ) ;
 proto_tree_add_uint_format_value ( rsvp_ethspec_subtree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "%u - Ethernet Bandwidth Profile" , tlv_type ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_length , tvb , offset + tlv_off + 2 , 2 , ENC_BIG_ENDIAN ) ;
 profile = tvb_get_guint8 ( tvb , offset + tlv_off + 4 ) ;
 ti3 = proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_profile , tvb , offset + tlv_off + 4 , 1 , ENC_NA ) ;
 ethspec_profile_subtree = proto_item_add_subtree ( ti3 , TREE ( TT_ETHSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( ethspec_profile_subtree , hf_rsvp_eth_tspec_tlv_color_mode , tvb , offset + tlv_off + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ethspec_profile_subtree , hf_rsvp_eth_tspec_tlv_coupling_flag , tvb , offset + tlv_off + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti3 , " %s %s" , ( profile & ( 1U << 1 ) ) ? "CM" : "" , ( profile & ( 1U << 0 ) ) ? "CF" : "" ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_index , tvb , offset + tlv_off + 5 , 1 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_reserved , tvb , offset + tlv_off + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_cir , tvb , offset + tlv_off + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_cbs , tvb , offset + tlv_off + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_eir , tvb , offset + tlv_off + 16 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_ebs , tvb , offset + tlv_off + 20 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "ETH profile: CIR=%.10g, CBS=%.10g, EIR=%.10g, " "EBS=%.10g" , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 8 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 12 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 16 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 20 ) ) ;
 case 3 : if ( tlv_len != 8 ) {
 proto_tree_add_expert_format ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset + tlv_off + 2 , 2 , "Invalid TLV length" ) ;
 return ;
 }
 bit_offset = ( offset << 5 ) + 31 ;
 proto_tree_add_bits_item ( rsvp_object_tree , hf_rsvp_eth_tspec_il2cp , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 proto_tree_add_bits_item ( rsvp_object_tree , hf_rsvp_eth_tspec_el2cp , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 255 : rsvp_ethspec_subtree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset + tlv_off , tlv_len , subtree_type , NULL , "RESERVED (RFC6003)" ) ;
 proto_tree_add_uint_format_value ( rsvp_ethspec_subtree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "%u (RESERVED)" , tlv_type ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_length , tvb , offset + tlv_off + 2 , 2 , ENC_BIG_ENDIAN ) ;
 break ;
 case 129 : rsvp_ethspec_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + tlv_off , tlv_len , subtree_type , NULL , "Ethernet Bandwidth Profile TLV: CIR=%.10g, CBS=%.10g, " "EIR=%.10g, EBS=%.10g" , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 8 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 12 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 16 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 20 ) ) ;
 proto_tree_add_uint_format_value ( rsvp_ethspec_subtree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "%u - Ethernet Bandwidth Profile" , tlv_type ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_length , tvb , offset + tlv_off + 2 , 2 , ENC_BIG_ENDIAN ) ;
 profile = tvb_get_guint8 ( tvb , offset + tlv_off + 4 ) ;
 ti3 = proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_profile , tvb , offset + tlv_off + 4 , 1 , ENC_BIG_ENDIAN ) ;
 ethspec_profile_subtree = proto_item_add_subtree ( ti3 , TREE ( TT_ETHSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( ethspec_profile_subtree , hf_rsvp_eth_tspec_tlv_color_mode , tvb , offset + tlv_off + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ethspec_profile_subtree , hf_rsvp_eth_tspec_tlv_coupling_flag , tvb , offset + tlv_off + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti3 , " %s %s" , ( profile & ( 1U << 1 ) ) ? "CM" : "" , ( profile & ( 1U << 0 ) ) ? "CF" : "" ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_index , tvb , offset + tlv_off + 5 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_reserved , tvb , offset + tlv_off + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_cir , tvb , offset + tlv_off + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_cbs , tvb , offset + tlv_off + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_eir , tvb , offset + tlv_off + 16 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_ethspec_subtree , hf_rsvp_eth_tspec_ebs , tvb , offset + tlv_off + 20 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "ETH profile: CIR=%.10g, CBS=%.10g, EIR=%.10g, " "EBS=%.10g" , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 8 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 12 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 16 ) , tvb_get_ntohieee_float ( tvb , offset + tlv_off + 20 ) ) ;
 break ;
 default : proto_tree_add_uint_format ( rsvp_object_tree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "Unknown TLV: %u" , tlv_type ) ;
 break ;
 }
 tlv_off += tlv_len ;
 }
 }