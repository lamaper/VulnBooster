static void update_offset_hash_table ( OffsetHashTable tbl , u32 * kid , off_t off ) {
 struct off_item * k ;
 ( void ) off ;
 for ( k = tbl [ ( kid [ 1 ] & 0x07ff ) ] ;
 k ;
 k = k -> next ) {
 if ( k -> kid [ 0 ] == kid [ 0 ] && k -> kid [ 1 ] == kid [ 1 ] ) {
 return ;
 }
 }
 k = new_offset_item ( ) ;
 k -> kid [ 0 ] = kid [ 0 ] ;
 k -> kid [ 1 ] = kid [ 1 ] ;
 k -> next = tbl [ ( kid [ 1 ] & 0x07ff ) ] ;
 tbl [ ( kid [ 1 ] & 0x07ff ) ] = k ;
 }