static void remove_short_at_index ( H264Context * h , int i ) {
 assert ( i >= 0 && i < h -> short_ref_count ) ;
 h -> short_ref [ i ] = NULL ;
 if ( -- h -> short_ref_count ) memmove ( & h -> short_ref [ i ] , & h -> short_ref [ i + 1 ] , ( h -> short_ref_count - i ) * sizeof ( Picture * ) ) ;
 }