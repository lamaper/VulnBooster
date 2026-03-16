static void test_bufferevent ( void ) {
 struct bufferevent * bev1 , * bev2 ;
 char buffer [ 8333 ] ;
 int i ;
 setup_test ( "Bufferevent: " ) ;
 bev1 = bufferevent_new ( pair [ 0 ] , readcb , writecb , errorcb , NULL ) ;
 bev2 = bufferevent_new ( pair [ 1 ] , readcb , writecb , errorcb , NULL ) ;
 bufferevent_disable ( bev1 , EV_READ ) ;
 bufferevent_enable ( bev2 , EV_READ ) ;
 for ( i = 0 ;
 i < sizeof ( buffer ) ;
 i ++ ) buffer [ i ] = i ;
 bufferevent_write ( bev1 , buffer , sizeof ( buffer ) ) ;
 event_dispatch ( ) ;
 bufferevent_free ( bev1 ) ;
 bufferevent_free ( bev2 ) ;
 if ( test_ok != 2 ) test_ok = 0 ;
 cleanup_test ( ) ;
 }