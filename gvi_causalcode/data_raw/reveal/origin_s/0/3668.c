static void test_simplewrite ( void ) {
 struct event ev ;
 setup_test ( "Simple write: " ) ;
 event_set ( & ev , pair [ 0 ] , EV_WRITE , simple_write_cb , & ev ) ;
 if ( event_add ( & ev , NULL ) == - 1 ) exit ( 1 ) ;
 event_dispatch ( ) ;
 cleanup_test ( ) ;
 }