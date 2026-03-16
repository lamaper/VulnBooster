static int dissect_pcp_partial_pmid ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset ) {
 proto_item * pcp_pmid_item ;
 proto_tree * pcp_pmid_tree ;
 guint32 bits_offset ;
 guint32 pmid ;
 guint8 * name ;
 bits_offset = offset * 8 ;
 pmid = tvb_get_ntohl ( tvb , offset ) ;
 name = get_name_from_pmid ( pmid , pinfo ) ;
 pcp_pmid_item = proto_tree_add_item ( tree , hf_pcp_pmid , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( pcp_pmid_item , " (%s)" , name ) ;
 pcp_pmid_tree = proto_item_add_subtree ( pcp_pmid_item , ett_pcp ) ;
 proto_tree_add_bits_item ( pcp_pmid_tree , hf_pcp_pmid_flag , tvb , bits_offset , 1 , ENC_BIG_ENDIAN ) ;
 bits_offset += 1 ;
 proto_tree_add_bits_item ( pcp_pmid_tree , hf_pcp_pmid_domain , tvb , bits_offset , 9 , ENC_BIG_ENDIAN ) ;
 bits_offset += 9 ;
 proto_tree_add_bits_item ( pcp_pmid_tree , hf_pcp_pmid_cluster , tvb , bits_offset , 12 , ENC_BIG_ENDIAN ) ;
 bits_offset += 12 ;
 proto_tree_add_bits_item ( pcp_pmid_tree , hf_pcp_pmid_item , tvb , bits_offset , 10 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 return offset ;
 }