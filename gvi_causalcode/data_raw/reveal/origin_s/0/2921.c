static int gettime ( struct event_base * base , struct timeval * tp ) {
 if ( base -> tv_cache . tv_sec ) {
 * tp = base -> tv_cache ;
 return ( 0 ) ;
 }

 if ( use_monotonic && clock_gettime ( CLOCK_MONOTONIC , & ts ) == 0 ) {
 tp -> tv_sec = ts . tv_sec ;
 tp -> tv_usec = ts . tv_nsec / 1000 ;
 return ( 0 ) ;
 }

 return ( evutil_gettimeofday ( tp , NULL ) ) ;
 }