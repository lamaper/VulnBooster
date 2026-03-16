static int dissect_pcp_message_pmns_child ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_pmns_child_item ;
 proto_tree * pcp_pmns_child_tree ;
 guint32 name_len ;
 pcp_pmns_child_item = proto_tree_add_item ( tree , hf_pcp_pmns_child , tvb , offset , - 1 , ENC_NA ) ;
 pcp_pmns_child_tree = proto_item_add_subtree ( pcp_pmns_child_item , ett_pcp ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_PMNS_CHILD , packettypenames , "Unknown Type:0x%02x" ) ) ;
 proto_tree_add_item ( pcp_pmns_child_tree , hf_pcp_pmns_subtype , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_child_tree , hf_pcp_pmns_namelen , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 name_len = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_child_tree , hf_pcp_pmns_name , tvb , offset , name_len , ENC_ASCII | ENC_NA ) ;
 offset += 4 ;
 return offset ;
 }