static void test_simpleread ( void ) {
 struct event ev ;
 setup_test ( "Simple read: " ) ;
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 shutdown ( pair [ 0 ] , SHUT_WR ) ;
 event_set ( & ev , pair [ 1 ] , EV_READ , simple_read_cb , & ev ) ;
 if ( event_add ( & ev , NULL ) == - 1 ) exit ( 1 ) ;
 event_dispatch ( ) ;
 cleanup_test ( ) ;
 }