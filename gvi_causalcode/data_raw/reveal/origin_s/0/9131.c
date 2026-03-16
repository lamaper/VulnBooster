static void http_chunked_writecb ( struct bufferevent * bev , void * arg ) {
 if ( EVBUFFER_LENGTH ( EVBUFFER_OUTPUT ( bev ) ) == 0 ) {
 bufferevent_enable ( bev , EV_READ ) ;
 test_ok ++ ;
 }
 }