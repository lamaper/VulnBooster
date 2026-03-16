static void test_free_active_base ( void ) {
 struct event_base * base1 ;
 struct event ev1 ;
 setup_test ( "Free active base: " ) ;
 base1 = event_init ( ) ;
 event_set ( & ev1 , pair [ 1 ] , EV_READ , simple_read_cb , & ev1 ) ;
 event_base_set ( base1 , & ev1 ) ;
 event_add ( & ev1 , NULL ) ;
 event_base_free ( base1 ) ;
 test_ok = 1 ;
 cleanup_test ( ) ;
 }