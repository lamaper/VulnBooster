static void test_simpletimeout ( void ) {
 struct timeval tv ;
 struct event ev ;
 setup_test ( "Simple timeout: " ) ;
 tv . tv_usec = 0 ;
 tv . tv_sec = SECONDS ;
 evtimer_set ( & ev , timeout_cb , NULL ) ;
 evtimer_add ( & ev , & tv ) ;
 evutil_gettimeofday ( & tset , NULL ) ;
 event_dispatch ( ) ;
 cleanup_test ( ) ;
 }