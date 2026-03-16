static int dissect_pcp_message_instance_req ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_instance_req_item ;
 proto_tree * pcp_instance_req_tree ;
 guint32 name_len ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_INSTANCE_REQ , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_instance_req_item = proto_tree_add_item ( tree , hf_pcp_instance_req , tvb , offset , - 1 , ENC_NA ) ;
 pcp_instance_req_tree = proto_item_add_subtree ( pcp_instance_req_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_instance_req_tree , hf_pcp_instance_indom , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 offset = dissect_pcp_partial_when ( tvb , pinfo , pcp_instance_req_tree , offset ) ;
 proto_tree_add_item ( pcp_instance_req_tree , hf_pcp_pmid_inst , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_instance_req_tree , hf_pcp_instance_namelen , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 name_len = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 if ( name_len > 0 ) {
 proto_tree_add_item ( pcp_instance_req_tree , hf_pcp_instance_name , tvb , offset , name_len , ENC_ASCII | ENC_NA ) ;
 offset += name_len ;
 }
 return offset ;
 }