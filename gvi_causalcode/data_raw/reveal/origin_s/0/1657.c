static void test_loopexit_multiple ( void ) {
 struct timeval tv ;
 struct event_base * base ;
 setup_test ( "Loop Multiple exit: " ) ;
 base = event_base_new ( ) ;
 tv . tv_usec = 0 ;
 tv . tv_sec = 1 ;
 event_base_loopexit ( base , & tv ) ;
 tv . tv_usec = 0 ;
 tv . tv_sec = 2 ;
 event_base_loopexit ( base , & tv ) ;
 event_base_dispatch ( base ) ;
 event_base_free ( base ) ;
 test_ok = 1 ;
 cleanup_test ( ) ;
 }