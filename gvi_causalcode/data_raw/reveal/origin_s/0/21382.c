void min_heap_shift_down_ ( min_heap_t * s , unsigned hole_index , struct event * e ) {
 unsigned min_child = 2 * ( hole_index + 1 ) ;
 while ( min_child <= s -> n ) {
 min_child -= min_child == s -> n || min_heap_elem_greater ( s -> p [ min_child ] , s -> p [ min_child - 1 ] ) ;
 if ( ! ( min_heap_elem_greater ( e , s -> p [ min_child ] ) ) ) break ;
 ( s -> p [ hole_index ] = s -> p [ min_child ] ) -> min_heap_idx = hole_index ;
 hole_index = min_child ;
 min_child = 2 * ( hole_index + 1 ) ;
 }
 min_heap_shift_up_ ( s , hole_index , e ) ;
 }