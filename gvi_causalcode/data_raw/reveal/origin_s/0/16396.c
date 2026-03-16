static void mi_collect_stats_nonulls_first ( HA_KEYSEG * keyseg , ulonglong * notnull , uchar * key ) {
 uint first_null , kp ;
 first_null = ( uint ) ( ha_find_null ( keyseg , key ) - keyseg ) ;
 for ( kp = 0 ;
 kp < first_null ;
 kp ++ ) notnull [ kp ] ++ ;
 }