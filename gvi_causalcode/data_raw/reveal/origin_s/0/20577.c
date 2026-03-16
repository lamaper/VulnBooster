static void http_multi_line_header_test ( void ) {
 struct bufferevent * bev ;
 int fd ;
 const char * http_start_request ;
 short port = - 1 ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing HTTP Server with multi line: " ) ;
 http = http_setup ( & port , NULL ) ;
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , http_readcb , http_writecb , http_errorcb , NULL ) ;
 http_start_request = "GET /test HTTP/1.1\r\n" "Host: somehost\r\n" "Connection: close\r\n" "X-Multi: aaaaaaaa\r\n" " a\r\n" "\tEND\r\n" "X-Last: last\r\n" "\r\n" ;
 bufferevent_write ( bev , http_start_request , strlen ( http_start_request ) ) ;
 event_dispatch ( ) ;
 bufferevent_free ( bev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 evhttp_free ( http ) ;
 if ( test_ok != 4 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }