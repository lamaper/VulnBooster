static void close_detect_launch ( int fd , short what , void * arg ) {
 struct evhttp_connection * evcon = arg ;
 struct evhttp_request * req ;
 req = evhttp_request_new ( close_detect_done , NULL ) ;
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/test" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 }