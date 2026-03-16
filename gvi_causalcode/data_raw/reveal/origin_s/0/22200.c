static void http_basic_test ( void ) {
 struct timeval tv ;
 struct bufferevent * bev ;
 int fd ;
 const char * http_request ;
 short port = - 1 ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing Basic HTTP Server: " ) ;
 http = http_setup ( & port , NULL ) ;
 if ( evhttp_bind_socket ( http , "127.0.0.1" , port + 1 ) == - 1 ) {
 fprintf ( stdout , "FAILED (bind)\n" ) ;
 exit ( 1 ) ;
 }
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , http_readcb , http_writecb , http_errorcb , NULL ) ;
 http_request = "GET /test HTTP/1.1\r\n" "Host: some" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 timerclear ( & tv ) ;
 tv . tv_usec = 10000 ;
 event_once ( - 1 , EV_TIMEOUT , http_complete_write , bev , & tv ) ;
 event_dispatch ( ) ;
 if ( test_ok != 3 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 bufferevent_free ( bev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 fd = http_connect ( "127.0.0.1" , port + 1 ) ;
 bev = bufferevent_new ( fd , http_readcb , http_writecb , http_errorcb , NULL ) ;
 http_request = "GET /test HTTP/1.1\r\n" "Host: somehost\r\n" "Connection: close\r\n" "\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 event_dispatch ( ) ;
 bufferevent_free ( bev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 evhttp_free ( http ) ;
 if ( test_ok != 5 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }