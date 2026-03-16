static void readcb ( struct bufferevent * bev , void * arg ) {
 if ( EVBUFFER_LENGTH ( bev -> input ) == 8333 ) {
 bufferevent_disable ( bev , EV_READ ) ;
 test_ok ++ ;
 }
 }