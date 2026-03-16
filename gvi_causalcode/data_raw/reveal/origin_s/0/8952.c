static void http_failure_readcb ( struct bufferevent * bev , void * arg ) {
 const char * what = "400 Bad Request" ;
 if ( evbuffer_find ( bev -> input , ( const unsigned char * ) what , strlen ( what ) ) != NULL ) {
 test_ok = 2 ;
 bufferevent_disable ( bev , EV_READ ) ;
 event_loopexit ( NULL ) ;
 }
 }