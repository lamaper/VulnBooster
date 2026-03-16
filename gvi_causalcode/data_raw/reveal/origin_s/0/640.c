void min_heap_shift_up_ ( min_heap_t * s , unsigned hole_index , struct event * e ) {
 unsigned parent = ( hole_index - 1 ) / 2 ;
 while ( hole_index && min_heap_elem_greater ( s -> p [ parent ] , e ) ) {
 ( s -> p [ hole_index ] = s -> p [ parent ] ) -> min_heap_idx = hole_index ;
 hole_index = parent ;
 parent = ( hole_index - 1 ) / 2 ;
 }
 ( s -> p [ hole_index ] = e ) -> min_heap_idx = hole_index ;
 }