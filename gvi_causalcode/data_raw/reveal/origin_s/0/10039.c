static void create_pmid_to_name_map_from_candidates ( pcp_conv_info_t * pcp_conv_info , tvbuff_t * tvb , int offset , guint32 num_ids ) {
 guint32 i ;
 for ( i = 0 ;
 i < num_ids ;
 i ++ ) {
 guint32 pmid ;
 guint8 * pmid_name ;
 pmid = tvb_get_ntohl ( tvb , offset ) ;
 pmid_name = * ( guint8 * * ) wmem_array_index ( pcp_conv_info -> pmid_name_candidates , i ) ;
 if ( wmem_map_lookup ( pcp_conv_info -> pmid_to_name , GINT_TO_POINTER ( pmid ) ) == NULL ) {
 wmem_map_insert ( pcp_conv_info -> pmid_to_name , GINT_TO_POINTER ( pmid ) , pmid_name ) ;
 }
 offset += 4 ;
 }
 }