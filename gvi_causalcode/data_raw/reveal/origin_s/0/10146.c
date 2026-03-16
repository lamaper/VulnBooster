static void populate_pmids_to_names ( packet_info * pinfo , tvbuff_t * tvb , int offset , guint32 num_ids ) {
 pcp_conv_info_t * pcp_conv_info ;
 guint number_of_name_candidates ;
 pcp_conv_info = get_pcp_conversation_info ( pinfo ) ;
 number_of_name_candidates = wmem_array_get_count ( pcp_conv_info -> pmid_name_candidates ) ;
 if ( number_of_name_candidates == num_ids && has_unprocessed_pmns_names_frame ( pcp_conv_info ) ) {
 create_pmid_to_name_map_from_candidates ( pcp_conv_info , tvb , offset , num_ids ) ;
 pcp_conv_info -> last_processed_pmns_names_frame = pcp_conv_info -> last_pmns_names_frame ;
 }
 pcp_conv_info -> pmid_name_candidates = wmem_array_new ( wmem_file_scope ( ) , sizeof ( guint8 * ) ) ;
 }