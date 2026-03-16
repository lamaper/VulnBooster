static body_parts * * get_body_parts ( mac_is_channel * ch ) {
 body_parts * * bpa = ( body_parts * * ) g_hash_table_lookup ( mac_is_fragments , ch ) ;
 if ( bpa == NULL ) {
 mac_is_channel * channel ;
 guint16 i ;
 bpa = wmem_alloc_array ( wmem_file_scope ( ) , body_parts * , MAX_TSN ) ;
 for ( i = 0 ;
 i < MAX_TSN ;
 i ++ ) {
 bpa [ i ] = wmem_new0 ( wmem_file_scope ( ) , body_parts ) ;
 }
 channel = wmem_new ( wmem_file_scope ( ) , mac_is_channel ) ;
 * channel = * ch ;
 g_hash_table_insert ( mac_is_fragments , channel , bpa ) ;
 }
 return bpa ;
 }