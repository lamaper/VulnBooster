static void http_chunked_test ( void ) {
 struct bufferevent * bev ;
 int fd ;
 const char * http_request ;
 short port = - 1 ;
 struct timeval tv_start , tv_end ;
 struct evhttp_connection * evcon = NULL ;
 struct evhttp_request * req = NULL ;
 int i ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing Chunked HTTP Reply: " ) ;
 http = http_setup ( & port , NULL ) ;
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , http_chunked_readcb , http_chunked_writecb , http_chunked_errorcb , NULL ) ;
 http_request = "GET /chunked HTTP/1.1\r\n" "Host: somehost\r\n" "Connection: close\r\n" "\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 evutil_gettimeofday ( & tv_start , NULL ) ;
 event_dispatch ( ) ;
 evutil_gettimeofday ( & tv_end , NULL ) ;
 evutil_timersub ( & tv_end , & tv_start , & tv_end ) ;
 if ( tv_end . tv_sec >= 1 ) {
 fprintf ( stdout , "FAILED (time)\n" ) ;
 exit ( 1 ) ;
 }
 if ( test_ok != 2 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 evcon = evhttp_connection_new ( "127.0.0.1" , port ) ;
 if ( evcon == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 test_ok = 0 ;
 req = evhttp_request_new ( http_chunked_request_done , NULL ) ;
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/chunked" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 }
 evhttp_connection_free ( evcon ) ;
 evhttp_free ( http ) ;
 fprintf ( stdout , "OK\n" ) ;
 }