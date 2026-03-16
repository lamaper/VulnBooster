static void wm_readcb ( struct bufferevent * bev , void * arg ) {
 int len = EVBUFFER_LENGTH ( bev -> input ) ;
 static int nread ;
 assert ( len >= 10 && len <= 20 ) ;
 evbuffer_drain ( bev -> input , len ) ;
 nread += len ;
 if ( nread == 65000 ) {
 bufferevent_disable ( bev , EV_READ ) ;
 test_ok ++ ;
 }
 }