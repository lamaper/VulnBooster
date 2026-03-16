static int dissect_pcp_message_desc_req ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_desc_req_item ;
 proto_tree * pcp_desc_req_tree ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_DESC_REQ , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_desc_req_item = proto_tree_add_item ( tree , hf_pcp_desc_req , tvb , offset , - 1 , ENC_NA ) ;
 pcp_desc_req_tree = proto_item_add_subtree ( pcp_desc_req_item , ett_pcp ) ;
 offset = dissect_pcp_partial_pmid ( tvb , pinfo , pcp_desc_req_tree , offset ) ;
 return offset ;
 }