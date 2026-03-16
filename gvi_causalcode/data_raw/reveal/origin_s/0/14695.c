static int dissect_pcp_message_fetch ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_fetch_item ;
 proto_tree * pcp_fetch_tree ;
 guint32 num_pmid ;
 guint32 i ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_FETCH , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_fetch_item = proto_tree_add_item ( tree , hf_pcp_fetch , tvb , offset , - 1 , ENC_NA ) ;
 pcp_fetch_tree = proto_item_add_subtree ( pcp_fetch_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_fetch_tree , hf_pcp_ctxnum , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 offset = dissect_pcp_partial_when ( tvb , pinfo , pcp_fetch_tree , offset ) ;
 proto_tree_add_item ( pcp_fetch_tree , hf_pcp_fetch_numpmid , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_pmid = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < num_pmid ;
 i ++ ) {
 offset = dissect_pcp_partial_pmid ( tvb , pinfo , pcp_fetch_tree , offset ) ;
 }
 return offset ;
 }