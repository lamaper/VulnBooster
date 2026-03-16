struct event_base * event_base_new ( void ) {
 int i ;
 struct event_base * base ;
 if ( ( base = calloc ( 1 , sizeof ( struct event_base ) ) ) == NULL ) event_err ( 1 , "%s: calloc" , __func__ ) ;
 gettime ( base , & base -> event_tv ) ;
 min_heap_ctor ( & base -> timeheap ) ;
 TAILQ_INIT ( & base -> eventqueue ) ;
 base -> sig . ev_signal_pair [ 0 ] = - 1 ;
 base -> sig . ev_signal_pair [ 1 ] = - 1 ;
 base -> evbase = NULL ;
 for ( i = 0 ;
 eventops [ i ] && ! base -> evbase ;
 i ++ ) {
 base -> evsel = eventops [ i ] ;
 base -> evbase = base -> evsel -> init ( base ) ;
 }
 if ( base -> evbase == NULL ) event_errx ( 1 , "%s: no event mechanism available" , __func__ ) ;
 if ( evutil_getenv ( "EVENT_SHOW_METHOD" ) ) event_msgx ( "libevent using: %s\n" , base -> evsel -> name ) ;
 event_base_priority_init ( base , 1 ) ;
 return ( base ) ;
 }