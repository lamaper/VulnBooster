static void test_combined ( void ) {
 struct both r1 , r2 , w1 , w2 ;
 setup_test ( "Combined read/write: " ) ;
 memset ( & r1 , 0 , sizeof ( r1 ) ) ;
 memset ( & r2 , 0 , sizeof ( r2 ) ) ;
 memset ( & w1 , 0 , sizeof ( w1 ) ) ;
 memset ( & w2 , 0 , sizeof ( w2 ) ) ;
 w1 . nread = 4096 ;
 w2 . nread = 8192 ;
 event_set ( & r1 . ev , pair [ 0 ] , EV_READ , combined_read_cb , & r1 ) ;
 event_set ( & w1 . ev , pair [ 0 ] , EV_WRITE , combined_write_cb , & w1 ) ;
 event_set ( & r2 . ev , pair [ 1 ] , EV_READ , combined_read_cb , & r2 ) ;
 event_set ( & w2 . ev , pair [ 1 ] , EV_WRITE , combined_write_cb , & w2 ) ;
 if ( event_add ( & r1 . ev , NULL ) == - 1 ) exit ( 1 ) ;
 if ( event_add ( & w1 . ev , NULL ) ) exit ( 1 ) ;
 if ( event_add ( & r2 . ev , NULL ) ) exit ( 1 ) ;
 if ( event_add ( & w2 . ev , NULL ) ) exit ( 1 ) ;
 event_dispatch ( ) ;
 if ( r1 . nread == 8192 && r2 . nread == 4096 ) test_ok = 1 ;
 cleanup_test ( ) ;
 }