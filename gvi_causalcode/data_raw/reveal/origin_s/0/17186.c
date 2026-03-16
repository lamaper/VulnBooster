static int mi_collect_stats_nonulls_next ( HA_KEYSEG * keyseg , ulonglong * notnull , uchar * prev_key , uchar * last_key ) {
 uint diffs [ 2 ] ;
 uint first_null_seg , kp ;
 HA_KEYSEG * seg ;
 ha_key_cmp ( keyseg , prev_key , last_key , USE_WHOLE_KEY , SEARCH_FIND | SEARCH_NULL_ARE_NOT_EQUAL , diffs ) ;
 seg = keyseg + diffs [ 0 ] - 1 ;
 first_null_seg = ( uint ) ( ha_find_null ( seg , last_key + diffs [ 1 ] ) - keyseg ) ;
 for ( kp = 0 ;
 kp < first_null_seg ;
 kp ++ ) notnull [ kp ] ++ ;
 return diffs [ 0 ] ;
 }