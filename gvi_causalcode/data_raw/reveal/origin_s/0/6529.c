int event_del ( struct event * ev ) {
 struct event_base * base ;
 event_debug ( ( "event_del: %p, callback %p" , ev , ev -> ev_callback ) ) ;
 if ( ev -> ev_base == NULL ) return ( - 1 ) ;
 base = ev -> ev_base ;
 assert ( ! ( ev -> ev_flags & ~ EVLIST_ALL ) ) ;
 if ( ev -> ev_ncalls && ev -> ev_pncalls ) {
 * ev -> ev_pncalls = 0 ;
 }
 if ( ev -> ev_flags & EVLIST_TIMEOUT ) event_queue_remove ( base , ev , EVLIST_TIMEOUT ) ;
 if ( ev -> ev_flags & EVLIST_ACTIVE ) event_queue_remove ( base , ev , EVLIST_ACTIVE ) ;
 if ( ev -> ev_flags & EVLIST_INSERTED ) {
 event_queue_remove ( base , ev , EVLIST_INSERTED ) ;
 return ( base -> evsel -> del ( base -> evbase , ev ) ) ;
 }
 return ( 0 ) ;
 }