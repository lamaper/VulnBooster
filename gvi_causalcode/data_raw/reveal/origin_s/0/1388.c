static void add_candidate_name_for_pmid_resolution ( packet_info * pinfo , tvbuff_t * tvb , int offset , int name_len ) {
 pcp_conv_info_t * pcp_conv_info ;
 guint8 * name ;
 pcp_conv_info = get_pcp_conversation_info ( pinfo ) ;
 if ( is_unvisited_pmns_names_frame ( pinfo ) ) {
 name = tvb_get_string_enc ( wmem_file_scope ( ) , tvb , offset , name_len , ENC_ASCII ) ;
 wmem_array_append_one ( pcp_conv_info -> pmid_name_candidates , name ) ;
 }
 }