int event_reinit ( struct event_base * base ) {
 const struct eventop * evsel = base -> evsel ;
 void * evbase = base -> evbase ;
 int res = 0 ;
 struct event * ev ;
 if ( ! evsel -> need_reinit ) return ( 0 ) ;
 if ( base -> sig . ev_signal_added ) {
 event_queue_remove ( base , & base -> sig . ev_signal , EVLIST_INSERTED ) ;
 if ( base -> sig . ev_signal . ev_flags & EVLIST_ACTIVE ) event_queue_remove ( base , & base -> sig . ev_signal , EVLIST_ACTIVE ) ;
 base -> sig . ev_signal_added = 0 ;
 }
 if ( base -> evsel -> dealloc != NULL ) base -> evsel -> dealloc ( base , base -> evbase ) ;
 evbase = base -> evbase = evsel -> init ( base ) ;
 if ( base -> evbase == NULL ) event_errx ( 1 , "%s: could not reinitialize event mechanism" , __func__ ) ;
 TAILQ_FOREACH ( ev , & base -> eventqueue , ev_next ) {
 if ( evsel -> add ( evbase , ev ) == - 1 ) res = - 1 ;
 }
 return ( res ) ;
 }