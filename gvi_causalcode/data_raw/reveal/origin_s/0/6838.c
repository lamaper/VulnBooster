static int dissect_pcp_message_text_req ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_text_req_item ;
 proto_tree * pcp_text_req_tree ;
 proto_item * pcp_text_req_type_item ;
 proto_tree * pcp_text_req_type_tree ;
 guint32 bits_offset ;
 guint32 type ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_TEXT_REQ , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_text_req_item = proto_tree_add_item ( tree , hf_pcp_text_req , tvb , offset , - 1 , ENC_NA ) ;
 pcp_text_req_tree = proto_item_add_subtree ( pcp_text_req_item , ett_pcp ) ;
 type = tvb_get_ntohl ( tvb , offset + 4 ) ;
 if ( type & PM_TEXT_PMID ) {
 offset = dissect_pcp_partial_pmid ( tvb , pinfo , pcp_text_req_tree , offset ) ;
 }
 else if ( type & PM_TEXT_INDOM ) {
 proto_tree_add_item ( pcp_text_req_tree , hf_pcp_instance_indom , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 }
 pcp_text_req_type_item = proto_tree_add_item ( pcp_text_req_tree , hf_pcp_text_type , tvb , offset , 4 , ENC_NA ) ;
 pcp_text_req_type_tree = proto_item_add_subtree ( pcp_text_req_type_item , ett_pcp ) ;
 bits_offset = offset * 8 + 28 ;
 proto_tree_add_bits_item ( pcp_text_req_type_tree , hf_pcp_text_type_ident , tvb , bits_offset , 2 , ENC_BIG_ENDIAN ) ;
 bits_offset += 2 ;
 proto_tree_add_bits_item ( pcp_text_req_type_tree , hf_pcp_text_type_format , tvb , bits_offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 return offset ;
 }