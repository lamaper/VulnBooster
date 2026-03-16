int min_heap_reserve ( min_heap_t * s , unsigned n ) {
 if ( s -> a < n ) {
 struct event * * p ;
 unsigned a = s -> a ? s -> a * 2 : 8 ;
 if ( a < n ) a = n ;
 if ( ! ( p = ( struct event * * ) realloc ( s -> p , a * sizeof * p ) ) ) return - 1 ;
 s -> p = p ;
 s -> a = a ;
 }
 return 0 ;
 }