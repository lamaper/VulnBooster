static void test_multiplesignal ( void ) {
 struct event ev_one , ev_two ;
 struct itimerval itv ;
 setup_test ( "Multiple signal: " ) ;
 signal_set ( & ev_one , SIGALRM , signal_cb , & ev_one ) ;
 signal_add ( & ev_one , NULL ) ;
 signal_set ( & ev_two , SIGALRM , signal_cb , & ev_two ) ;
 signal_add ( & ev_two , NULL ) ;
 memset ( & itv , 0 , sizeof ( itv ) ) ;
 itv . it_value . tv_sec = 1 ;
 if ( setitimer ( ITIMER_REAL , & itv , NULL ) == - 1 ) goto skip_simplesignal ;
 event_dispatch ( ) ;
 skip_simplesignal : if ( signal_del ( & ev_one ) == - 1 ) test_ok = 0 ;
 if ( signal_del ( & ev_two ) == - 1 ) test_ok = 0 ;
 cleanup_test ( ) ;
 }