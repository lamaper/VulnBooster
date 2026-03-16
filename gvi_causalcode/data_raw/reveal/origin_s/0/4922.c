int event_add ( struct event * ev , const struct timeval * tv ) {
 struct event_base * base = ev -> ev_base ;
 const struct eventop * evsel = base -> evsel ;
 void * evbase = base -> evbase ;
 int res = 0 ;
 event_debug ( ( "event_add: event: %p, %s%s%scall %p" , ev , ev -> ev_events & EV_READ ? "EV_READ " : " " , ev -> ev_events & EV_WRITE ? "EV_WRITE " : " " , tv ? "EV_TIMEOUT " : " " , ev -> ev_callback ) ) ;
 assert ( ! ( ev -> ev_flags & ~ EVLIST_ALL ) ) ;
 if ( tv != NULL && ! ( ev -> ev_flags & EVLIST_TIMEOUT ) ) {
 if ( min_heap_reserve ( & base -> timeheap , + min_heap_size ( & base -> timeheap ) ) == - 1 ) return ( - 1 ) ;
 }
 if ( ( ev -> ev_events & ( EV_READ | EV_WRITE | EV_SIGNAL ) ) && ! ( ev -> ev_flags & ( EVLIST_INSERTED | EVLIST_ACTIVE ) ) ) {
 res = evsel -> add ( evbase , ev ) ;
 if ( res != - 1 ) event_queue_insert ( base , ev , EVLIST_INSERTED ) ;
 }
 if ( res != - 1 && tv != NULL ) {
 struct timeval now ;
 if ( ev -> ev_flags & EVLIST_TIMEOUT ) event_queue_remove ( base , ev , EVLIST_TIMEOUT ) ;
 if ( ( ev -> ev_flags & EVLIST_ACTIVE ) && ( ev -> ev_res & EV_TIMEOUT ) ) {
 if ( ev -> ev_ncalls && ev -> ev_pncalls ) {
 * ev -> ev_pncalls = 0 ;
 }
 event_queue_remove ( base , ev , EVLIST_ACTIVE ) ;
 }
 gettime ( base , & now ) ;
 evutil_timeradd ( & now , tv , & ev -> ev_timeout ) ;
 event_debug ( ( "event_add: timeout in %ld seconds, call %p" , tv -> tv_sec , ev -> ev_callback ) ) ;
 event_queue_insert ( base , ev , EVLIST_TIMEOUT ) ;
 }
 return ( res ) ;
 }