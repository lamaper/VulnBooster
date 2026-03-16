int event_base_loopbreak ( struct event_base * event_base ) {
 if ( event_base == NULL ) return ( - 1 ) ;
 event_base -> event_break = 1 ;
 return ( 0 ) ;
 }