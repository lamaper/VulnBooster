static int timeout_next ( struct event_base * base , struct timeval * * tv_p ) {
 struct timeval now ;
 struct event * ev ;
 struct timeval * tv = * tv_p ;
 if ( ( ev = min_heap_top ( & base -> timeheap ) ) == NULL ) {
 * tv_p = NULL ;
 return ( 0 ) ;
 }
 if ( gettime ( base , & now ) == - 1 ) return ( - 1 ) ;
 if ( evutil_timercmp ( & ev -> ev_timeout , & now , <= ) ) {
 evutil_timerclear ( tv ) ;
 return ( 0 ) ;
 }
 evutil_timersub ( & ev -> ev_timeout , & now , tv ) ;
 assert ( tv -> tv_sec >= 0 ) ;
 assert ( tv -> tv_usec >= 0 ) ;
 event_debug ( ( "timeout_next: in %ld seconds" , tv -> tv_sec ) ) ;
 return ( 0 ) ;
 }