static void test_multiple_events_for_same_fd ( void ) {
 struct event e1 , e2 ;
 setup_test ( "Multiple events for same fd: " ) ;
 event_set ( & e1 , pair [ 0 ] , EV_READ , test_multiple_cb , NULL ) ;
 event_add ( & e1 , NULL ) ;
 event_set ( & e2 , pair [ 0 ] , EV_WRITE , test_multiple_cb , NULL ) ;
 event_add ( & e2 , NULL ) ;
 event_loop ( EVLOOP_ONCE ) ;
 event_del ( & e2 ) ;
 write ( pair [ 1 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 event_loop ( EVLOOP_ONCE ) ;
 event_del ( & e1 ) ;
 if ( test_ok != 3 ) test_ok = 0 ;
 cleanup_test ( ) ;
 }