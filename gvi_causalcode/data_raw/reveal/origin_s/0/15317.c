static int dissect_pcp_message_pmns_ids ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_pmns_ids_item ;
 proto_tree * pcp_pmns_ids_tree ;
 guint32 num_ids ;
 guint32 i ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_PMNS_IDS , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_pmns_ids_item = proto_tree_add_item ( tree , hf_pcp_pmns_ids , tvb , offset , - 1 , ENC_NA ) ;
 pcp_pmns_ids_tree = proto_item_add_subtree ( pcp_pmns_ids_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_pmns_ids_tree , hf_pcp_pmns_ids_status , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_ids_tree , hf_pcp_pmns_ids_numids , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_ids = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 populate_pmids_to_names ( pinfo , tvb , offset , num_ids ) ;
 for ( i = 0 ;
 i < num_ids ;
 i ++ ) {
 offset = dissect_pcp_partial_pmid ( tvb , pinfo , pcp_pmns_ids_tree , offset ) ;
 }
 return offset ;
 }