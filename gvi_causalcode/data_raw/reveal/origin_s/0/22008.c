int min_heap_push ( min_heap_t * s , struct event * e ) {
 if ( min_heap_reserve ( s , s -> n + 1 ) ) return - 1 ;
 min_heap_shift_up_ ( s , s -> n ++ , e ) ;
 return 0 ;
 }