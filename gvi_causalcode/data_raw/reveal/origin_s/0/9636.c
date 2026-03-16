static void evhttp_add_event ( struct event * ev , int timeout , int default_timeout ) {
 if ( timeout != 0 ) {
 struct timeval tv ;
 evutil_timerclear ( & tv ) ;
 tv . tv_sec = timeout != - 1 ? timeout : default_timeout ;
 event_add ( ev , & tv ) ;
 }
 else {
 event_add ( ev , NULL ) ;
 }
 }