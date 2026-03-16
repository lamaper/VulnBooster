static void update_offset_hash_table_from_kb ( OffsetHashTable tbl , KBNODE node , off_t off ) {
 for ( ;
 node ;
 node = node -> next ) {
 if ( node -> pkt -> pkttype == PKT_PUBLIC_KEY || node -> pkt -> pkttype == PKT_PUBLIC_SUBKEY ) {
 u32 aki [ 2 ] ;
 keyid_from_pk ( node -> pkt -> pkt . public_key , aki ) ;
 update_offset_hash_table ( tbl , aki , off ) ;
 }
 }
 }