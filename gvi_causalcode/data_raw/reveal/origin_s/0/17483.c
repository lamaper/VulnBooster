static int dissect_pcp_message_pmns_names ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_pmns_names_item ;
 proto_tree * pcp_pmns_names_tree ;
 proto_item * pcp_pmns_names_name_item ;
 proto_tree * pcp_pmns_names_name_tree ;
 guint32 is_pmns_names_status ;
 guint32 num_names ;
 guint32 name_len ;
 guint32 full_name_len ;
 guint32 padding ;
 guint32 i ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_PMNS_NAMES , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_pmns_names_item = proto_tree_add_item ( tree , hf_pcp_pmns_names , tvb , offset , - 1 , ENC_NA ) ;
 pcp_pmns_names_tree = proto_item_add_subtree ( pcp_pmns_names_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_pmns_names_tree , hf_pcp_pmns_names_nstrbytes , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_names_tree , hf_pcp_pmns_names_numstatus , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 is_pmns_names_status = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_pmns_names_tree , hf_pcp_pmns_names_numnames , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_names = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < num_names ;
 i ++ ) {
 if ( is_pmns_names_status ) {
 name_len = tvb_get_ntohl ( tvb , offset + 4 ) ;
 full_name_len = name_len + 8 ;
 }
 else {
 name_len = tvb_get_ntohl ( tvb , offset ) ;
 full_name_len = name_len + 4 ;
 }
 pcp_pmns_names_name_item = proto_tree_add_item ( pcp_pmns_names_tree , hf_pcp_pmns_names_nametree , tvb , offset , full_name_len , ENC_NA ) ;
 pcp_pmns_names_name_tree = proto_item_add_subtree ( pcp_pmns_names_name_item , ett_pcp ) ;
 if ( is_pmns_names_status ) {
 proto_tree_add_item ( pcp_pmns_names_name_tree , hf_pcp_pmns_names_nametree_status , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 }
 proto_tree_add_item ( pcp_pmns_names_name_tree , hf_pcp_pmns_names_nametree_namelen , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 if ( client_to_server ( pinfo ) ) {
 add_candidate_name_for_pmid_resolution ( pinfo , tvb , offset , name_len ) ;
 }
 proto_tree_add_item ( pcp_pmns_names_name_tree , hf_pcp_pmns_names_nametree_name , tvb , offset , name_len , ENC_ASCII | ENC_NA ) ;
 offset += name_len ;
 padding = name_len % 4 ;
 if ( padding != 0 ) {
 padding = 4 - padding ;
 proto_tree_add_item ( pcp_pmns_names_name_tree , hf_pcp_pdu_padding , tvb , offset , padding , ENC_NA ) ;
 offset += padding ;
 }
 }
 if ( client_to_server ( pinfo ) ) {
 mark_this_frame_as_last_pmns_names_frame ( pinfo ) ;
 }
 return offset ;
 }