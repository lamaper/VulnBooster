static void http_bad_request ( void ) {
 struct timeval tv ;
 struct bufferevent * bev ;
 int fd ;
 const char * http_request ;
 short port = - 1 ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing \"Bad Request\" on connection close: " ) ;
 http = http_setup ( & port , NULL ) ;
 if ( evhttp_bind_socket ( http , "127.0.0.1" , port + 1 ) == - 1 ) {
 fprintf ( stdout , "FAILED (bind)\n" ) ;
 exit ( 1 ) ;
 }
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , http_badreq_readcb , http_writecb , http_badreq_errorcb , NULL ) ;
 bufferevent_enable ( bev , EV_READ ) ;
 http_request = "" ;
 shutdown ( fd , SHUT_WR ) ;
 timerclear ( & tv ) ;
 tv . tv_usec = 10000 ;
 event_once ( - 1 , EV_TIMEOUT , http_badreq_successcb , bev , & tv ) ;
 event_dispatch ( ) ;
 bufferevent_free ( bev ) ;
 EVUTIL_CLOSESOCKET ( fd ) ;
 if ( test_ok != 0 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fd = http_connect ( "127.0.0.1" , port + 1 ) ;
 bev = bufferevent_new ( fd , http_badreq_readcb , http_writecb , http_badreq_errorcb , NULL ) ;
 bufferevent_enable ( bev , EV_READ ) ;
 http_request = "GET /badrequest HTTP/1.0\r\n" "Connection: Keep-Alive\r\n" "\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 timerclear ( & tv ) ;
 tv . tv_usec = 10000 ;
 event_once ( - 1 , EV_TIMEOUT , http_badreq_successcb , bev , & tv ) ;
 event_dispatch ( ) ;
 evhttp_free ( http ) ;
 if ( test_ok != 2 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }