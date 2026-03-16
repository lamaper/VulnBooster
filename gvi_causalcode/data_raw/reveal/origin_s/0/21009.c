static guint8 * get_name_from_pmid ( guint32 pmid , packet_info * pinfo ) {
 guint8 * name ;
 wmem_map_t * pmid_to_name ;
 pmid_to_name = get_pcp_conversation_info ( pinfo ) -> pmid_to_name ;
 name = ( guint8 * ) wmem_map_lookup ( pmid_to_name , GINT_TO_POINTER ( pmid ) ) ;
 if ( ! name ) {
 name = ( guint8 * ) wmem_strdup ( wmem_packet_scope ( ) , "Metric name unknown" ) ;
 }
 return name ;
 }