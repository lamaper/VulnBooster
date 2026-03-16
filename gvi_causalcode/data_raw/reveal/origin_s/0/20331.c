static int dissect_segment_unknown ( tvbuff_t * tvb , int offset , packet_info * pinfo _U_ , proto_tree * tree , int encoding ) {
 proto_item * subtree_item = NULL ;
 proto_tree * subtree = NULL ;
 int datalen = 0 ;
 int seglen = 0 ;
 seglen = lbmpdm_get_segment_length ( tvb , offset , encoding , & datalen ) ;
 subtree_item = proto_tree_add_none_format ( tree , hf_lbmpdm_segment , tvb , offset , seglen , "Unknown Segment" ) ;
 subtree = proto_item_add_subtree ( subtree_item , ett_lbmpdm_segment ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_next_hdr , tvb , offset + O_LBMPDM_SEG_HDR_T_NEXT_HDR , L_LBMPDM_SEG_HDR_T_NEXT_HDR , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_flags , tvb , offset + O_LBMPDM_SEG_HDR_T_FLAGS , L_LBMPDM_SEG_HDR_T_FLAGS , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_res , tvb , offset + O_LBMPDM_SEG_HDR_T_RES , L_LBMPDM_SEG_HDR_T_RES , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_len , tvb , offset + O_LBMPDM_SEG_HDR_T_LEN , L_LBMPDM_SEG_HDR_T_LEN , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_data , tvb , offset + L_LBMPDM_SEG_HDR_T , datalen , ENC_NA ) ;
 return ( seglen ) ;
 }