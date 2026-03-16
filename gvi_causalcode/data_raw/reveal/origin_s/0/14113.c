static void http_request_bad ( struct evhttp_request * req , void * arg ) {
 if ( req != NULL ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 test_ok = 1 ;
 event_loopexit ( NULL ) ;
 }