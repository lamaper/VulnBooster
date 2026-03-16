static void close_detect_done ( struct evhttp_request * req , void * arg ) {
 struct timeval tv ;
 if ( req == NULL || req -> response_code != HTTP_OK ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 test_ok = 1 ;
 timerclear ( & tv ) ;
 tv . tv_sec = 3 ;
 event_loopexit ( & tv ) ;
 }