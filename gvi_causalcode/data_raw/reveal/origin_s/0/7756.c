static OffsetHashTable new_offset_hash_table ( void ) {
 struct off_item * * tbl ;
 tbl = xmalloc_clear ( 2048 * sizeof * tbl ) ;
 return tbl ;
 }