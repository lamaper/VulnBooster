static void test_signal_assert ( void ) {
 struct event ev ;
 struct event_base * base = event_init ( ) ;
 test_ok = 0 ;
 printf ( "Signal handler assert: " ) ;
 signal_set ( & ev , SIGCONT , signal_cb , & ev ) ;
 signal_add ( & ev , NULL ) ;
 signal_del ( & ev ) ;
 raise ( SIGCONT ) ;
 if ( base -> sig . evsignal_caught ) test_ok = 0 ;
 else test_ok = 1 ;
 event_base_free ( base ) ;
 cleanup_test ( ) ;
 return ;
 }