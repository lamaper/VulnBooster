static int dissect_pcp_partial_when ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset ) {
 proto_item * pcp_when_item ;
 proto_tree * pcp_when_tree ;
 pcp_when_item = proto_tree_add_item ( tree , hf_pcp_when , tvb , offset , 8 , ENC_NA ) ;
 pcp_when_tree = proto_item_add_subtree ( pcp_when_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_when_tree , hf_pcp_when_sec , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_when_tree , hf_pcp_when_usec , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 return offset ;
 }