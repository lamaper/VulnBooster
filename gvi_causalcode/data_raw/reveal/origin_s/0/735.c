static void http_writecb ( struct bufferevent * bev , void * arg ) {
 if ( EVBUFFER_LENGTH ( bev -> output ) == 0 ) {
 bufferevent_enable ( bev , EV_READ ) ;
 test_ok ++ ;
 }
 }