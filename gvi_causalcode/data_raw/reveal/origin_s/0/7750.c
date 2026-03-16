static void test_immediatesignal ( void ) {
 struct event ev ;
 test_ok = 0 ;
 printf ( "Immediate signal: " ) ;
 signal_set ( & ev , SIGUSR1 , signal_cb , & ev ) ;
 signal_add ( & ev , NULL ) ;
 raise ( SIGUSR1 ) ;
 event_loop ( EVLOOP_NONBLOCK ) ;
 signal_del ( & ev ) ;
 cleanup_test ( ) ;
 }