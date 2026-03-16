static tvbuff_t * reassemble ( tvbuff_t * tvb , body_parts * * body_parts_array , guint16 head_tsn , guint length , mac_is_channel * ch , guint frame_num ) {
 mac_is_sdu * sdu ;
 mac_is_fragment * f ;
 guint16 i ;
 GHashTable * sdus ;
 sdus = ( GHashTable * ) g_hash_table_lookup ( mac_is_sdus , ch ) ;
 if ( sdus == NULL ) {
 mac_is_channel * channel ;
 sdus = g_hash_table_new ( mac_is_fragment_hash , mac_is_fragment_equal ) ;
 channel = wmem_new ( wmem_file_scope ( ) , mac_is_channel ) ;
 * channel = * ch ;
 g_hash_table_insert ( mac_is_sdus , channel , sdus ) ;
 }
 sdu = wmem_new ( wmem_file_scope ( ) , mac_is_sdu ) ;
 sdu -> length = 0 ;
 sdu -> data = ( guint8 * ) wmem_alloc ( wmem_file_scope ( ) , length ) ;
 f = body_parts_array [ head_tsn ] -> head ;
 g_hash_table_insert ( sdus , f , sdu ) ;
 body_parts_array [ head_tsn ] -> head = NULL ;
 mac_is_copy ( sdu , f , length , FALSE ) ;
 sdu -> fragments = f ;
 sdu -> frame_num = frame_num ;
 for ( i = ( head_tsn + 1 ) % MAX_TSN ;
 body_parts_array [ i ] -> middle != NULL ;
 i = ( i + 1 ) % MAX_TSN ) {
 f = f -> next = body_parts_array [ i ] -> middle ;
 g_hash_table_insert ( sdus , f , sdu ) ;
 body_parts_array [ i ] -> middle = NULL ;
 mac_is_copy ( sdu , f , length , FALSE ) ;
 }
 DISSECTOR_ASSERT ( body_parts_array [ i ] -> tail != NULL ) ;
 f -> next = body_parts_array [ i ] -> tail ;
 g_hash_table_insert ( sdus , f -> next , sdu ) ;
 body_parts_array [ i ] -> tail = NULL ;
 sdu -> tsn = i ;
 mac_is_copy ( sdu , f -> next , length , FALSE ) ;
 return tvb_new_child_real_data ( tvb , sdu -> data , sdu -> length , sdu -> length ) ;
 }