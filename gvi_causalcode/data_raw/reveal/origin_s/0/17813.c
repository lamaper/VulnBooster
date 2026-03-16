int min_heap_erase ( min_heap_t * s , struct event * e ) {
 if ( ( ( unsigned int ) - 1 ) != e -> min_heap_idx ) {
 struct event * last = s -> p [ -- s -> n ] ;
 unsigned parent = ( e -> min_heap_idx - 1 ) / 2 ;
 if ( e -> min_heap_idx > 0 && min_heap_elem_greater ( s -> p [ parent ] , last ) ) min_heap_shift_up_ ( s , e -> min_heap_idx , last ) ;
 else min_heap_shift_down_ ( s , e -> min_heap_idx , last ) ;
 e -> min_heap_idx = - 1 ;
 return 0 ;
 }
 return - 1 ;
 }