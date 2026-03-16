static void test_event_base_new ( void ) {
 struct event_base * base ;
 struct event ev1 ;
 setup_test ( "Event base new: " ) ;
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 shutdown ( pair [ 0 ] , SHUT_WR ) ;
 base = event_base_new ( ) ;
 event_set ( & ev1 , pair [ 1 ] , EV_READ , simple_read_cb , & ev1 ) ;
 event_base_set ( base , & ev1 ) ;
 event_add ( & ev1 , NULL ) ;
 event_base_dispatch ( base ) ;
 event_base_free ( base ) ;
 test_ok = 1 ;
 cleanup_test ( ) ;
 }