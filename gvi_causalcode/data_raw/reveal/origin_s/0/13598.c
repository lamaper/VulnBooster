static void http_failure_test ( void ) {
 struct bufferevent * bev ;
 int fd ;
 const char * http_request ;
 short port = - 1 ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing Bad HTTP Request: " ) ;
 http = http_setup ( & port , NULL ) ;
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , http_failure_readcb , http_writecb , http_errorcb , NULL ) ;
 http_request = "illegal request\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 event_dispatch ( ) ;
 bufferevent_free ( bev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 evhttp_free ( http ) ;
 if ( test_ok != 2 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }