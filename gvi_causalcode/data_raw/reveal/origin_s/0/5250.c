static void close_detect_cb ( struct evhttp_request * req , void * arg ) {
 struct evhttp_connection * evcon = arg ;
 struct timeval tv ;
 if ( req != NULL && req -> response_code != HTTP_OK ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 timerclear ( & tv ) ;
 tv . tv_sec = 3 ;
 event_once ( - 1 , EV_TIMEOUT , close_detect_launch , evcon , & tv ) ;
 }