struct event * min_heap_pop ( min_heap_t * s ) {
 if ( s -> n ) {
 struct event * e = * s -> p ;
 min_heap_shift_down_ ( s , 0u , s -> p [ -- s -> n ] ) ;
 e -> min_heap_idx = - 1 ;
 return e ;
 }
 return 0 ;
 }