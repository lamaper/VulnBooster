static struct off_item * lookup_offset_hash_table ( OffsetHashTable tbl , u32 * kid ) {
 struct off_item * k ;
 for ( k = tbl [ ( kid [ 1 ] & 0x07ff ) ] ;
 k ;
 k = k -> next ) if ( k -> kid [ 0 ] == kid [ 0 ] && k -> kid [ 1 ] == kid [ 1 ] ) return k ;
 return NULL ;
 }