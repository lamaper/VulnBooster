static void test_signal_dealloc ( void ) {
 struct event ev ;
 struct event_base * base = event_init ( ) ;
 printf ( "Signal dealloc: " ) ;
 signal_set ( & ev , SIGUSR1 , signal_cb , & ev ) ;
 signal_add ( & ev , NULL ) ;
 signal_del ( & ev ) ;
 event_base_free ( base ) ;
 test_ok = 1 ;
 cleanup_test ( ) ;
 }