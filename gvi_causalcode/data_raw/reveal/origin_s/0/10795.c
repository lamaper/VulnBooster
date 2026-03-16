static void http_terminate_chunked_test ( void ) {
 struct bufferevent * bev = NULL ;
 struct timeval tv ;
 const char * http_request ;
 short port = - 1 ;
 int fd = - 1 ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing Terminated Chunked Connection: " ) ;
 http = http_setup ( & port , NULL ) ;
 evhttp_del_cb ( http , "/test" ) ;
 evhttp_set_cb ( http , "/test" , terminate_chunked_cb , & terminate_state ) ;
 fd = http_connect ( "127.0.0.1" , port ) ;
 bev = bufferevent_new ( fd , terminate_readcb , http_writecb , http_errorcb , NULL ) ;
 terminate_state . fd = fd ;
 terminate_state . bev = bev ;
 http_request = "GET /test HTTP/1.1\r\n" "Host: some\r\n\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 evutil_timerclear ( & tv ) ;
 tv . tv_usec = 10000 ;
 event_once ( - 1 , EV_TIMEOUT , terminate_chunked_client , & terminate_state , & tv ) ;
 event_dispatch ( ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 if ( fd >= 0 ) EVUTIL_CLOSESOCKET ( fd ) ;
 if ( http ) evhttp_free ( http ) ;
 }