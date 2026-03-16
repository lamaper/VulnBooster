static void test_simplesignal ( void ) {
 struct event ev ;
 struct itimerval itv ;
 setup_test ( "Simple signal: " ) ;
 signal_set ( & ev , SIGALRM , signal_cb , & ev ) ;
 signal_add ( & ev , NULL ) ;
 signal_del ( & ev ) ;
 signal_add ( & ev , NULL ) ;
 memset ( & itv , 0 , sizeof ( itv ) ) ;
 itv . it_value . tv_sec = 1 ;
 if ( setitimer ( ITIMER_REAL , & itv , NULL ) == - 1 ) goto skip_simplesignal ;
 event_dispatch ( ) ;
 skip_simplesignal : if ( signal_del ( & ev ) == - 1 ) test_ok = 0 ;
 cleanup_test ( ) ;
 }