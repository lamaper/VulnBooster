static void test_persistent ( void ) {
 struct event ev , ev2 ;
 int i ;
 setup_test ( "Persist read/write: " ) ;
 memset ( rbuf , 0 , sizeof ( rbuf ) ) ;
 for ( i = 0 ;
 i < sizeof ( wbuf ) ;
 i ++ ) wbuf [ i ] = i ;
 roff = woff = 0 ;
 usepersist = 1 ;
 event_set ( & ev , pair [ 0 ] , EV_WRITE | EV_PERSIST , multiple_write_cb , & ev ) ;
 if ( event_add ( & ev , NULL ) == - 1 ) exit ( 1 ) ;
 event_set ( & ev2 , pair [ 1 ] , EV_READ | EV_PERSIST , multiple_read_cb , & ev2 ) ;
 if ( event_add ( & ev2 , NULL ) == - 1 ) exit ( 1 ) ;
 event_dispatch ( ) ;
 if ( roff == woff ) test_ok = memcmp ( rbuf , wbuf , sizeof ( wbuf ) ) == 0 ;
 cleanup_test ( ) ;
 }