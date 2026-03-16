static void test_loopbreak ( void ) {
 struct event ev1 , ev2 ;
 struct timeval tv ;
 setup_test ( "Loop break: " ) ;
 tv . tv_sec = 0 ;
 tv . tv_usec = 0 ;
 evtimer_set ( & ev1 , break_cb , NULL ) ;
 evtimer_add ( & ev1 , & tv ) ;
 evtimer_set ( & ev2 , fail_cb , NULL ) ;
 evtimer_add ( & ev2 , & tv ) ;
 event_dispatch ( ) ;
 evtimer_del ( & ev1 ) ;
 evtimer_del ( & ev2 ) ;
 cleanup_test ( ) ;
 }