unsigned long keydb_get_skipped_counter ( KEYDB_HANDLE hd ) {
 return hd ? hd -> skipped_long_blobs : 0 ;
 }