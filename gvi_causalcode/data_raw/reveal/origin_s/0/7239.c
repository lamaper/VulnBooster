static int dissect_pcp_message_pmns_traverse ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_pmns_traverse_item ;
 proto_tree * pcp_pmns_traverse_tree ;
 guint32 name_len ;
 guint32 padding ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_PMNS_TRAVERSE , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_pmns_traverse_item = proto_tree_add_item ( tree , hf_pcp_pmns_traverse , tvb , offset , - 1 , ENC_NA ) ;
 pcp_pmns_traverse_tree = proto_item_add_subtree ( pcp_pmns_traverse_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_pmns_traverse_tree , hf_pcp_pmns_subtype , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_traverse_tree , hf_pcp_pmns_namelen , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 name_len = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_traverse_tree , hf_pcp_pmns_name , tvb , offset , name_len , ENC_ASCII | ENC_NA ) ;
 offset += name_len ;
 padding = name_len % 4 ;
 if ( padding != 0 ) {
 padding = 4 - padding ;
 proto_tree_add_item ( pcp_pmns_traverse_tree , hf_pcp_pdu_padding , tvb , offset , padding , ENC_NA ) ;
 offset += padding ;
 }
 return offset ;
 }