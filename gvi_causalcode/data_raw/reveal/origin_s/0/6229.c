static void test_want_only_once ( void ) {
 struct event ev ;
 struct timeval tv ;
 setup_test ( "Want read only once: " ) ;
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 evutil_timerclear ( & tv ) ;
 tv . tv_sec = 1 ;
 event_loopexit ( & tv ) ;
 event_set ( & ev , pair [ 1 ] , EV_READ , read_once_cb , & ev ) ;
 if ( event_add ( & ev , NULL ) == - 1 ) exit ( 1 ) ;
 event_dispatch ( ) ;
 cleanup_test ( ) ;
 }