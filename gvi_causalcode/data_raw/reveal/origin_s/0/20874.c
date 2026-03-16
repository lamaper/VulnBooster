static void http_base_test ( void ) {
 struct bufferevent * bev ;
 int fd ;
 const char * http_request ;
 short port = - 1 ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing HTTP Server Event Base: " ) ;
 base = event_init ( ) ;
 event_init ( ) ;
 http = http_setup ( & port , base ) ;
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , http_readcb , http_writecb , http_errorcb , NULL ) ;
 bufferevent_base_set ( base , bev ) ;
 http_request = "GET /test HTTP/1.1\r\n" "Host: somehost\r\n" "Connection: close\r\n" "\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 event_base_dispatch ( base ) ;
 bufferevent_free ( bev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 evhttp_free ( http ) ;
 event_base_free ( base ) ;
 base = NULL ;
 if ( test_ok != 2 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }