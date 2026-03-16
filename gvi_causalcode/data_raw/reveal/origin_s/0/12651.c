static void http_errorcb ( struct bufferevent * bev , short what , void * arg ) {
 test_ok = - 2 ;
 event_loopexit ( NULL ) ;
 }