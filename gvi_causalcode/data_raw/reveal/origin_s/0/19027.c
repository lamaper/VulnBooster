struct event * min_heap_top ( min_heap_t * s ) {
 return s -> n ? * s -> p : 0 ;
 }