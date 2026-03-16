static void http_connection_test ( int persistent ) {
 short port = - 1 ;
 struct evhttp_connection * evcon = NULL ;
 struct evhttp_request * req = NULL ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing Request Connection Pipeline %s: " , persistent ? "(persistent)" : "" ) ;
 http = http_setup ( & port , NULL ) ;
 evcon = evhttp_connection_new ( "127.0.0.1" , port ) ;
 if ( evcon == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 req = evhttp_request_new ( http_request_done , NULL ) ;
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/test" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 test_ok = 0 ;
 req = evhttp_request_new ( http_request_done , NULL ) ;
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 if ( ! persistent ) evhttp_add_header ( req -> output_headers , "Connection" , "close" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/test" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 test_ok = 0 ;
 req = evhttp_request_new ( http_request_empty_done , NULL ) ;
 evhttp_add_header ( req -> output_headers , "Empty" , "itis" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/test" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 evhttp_connection_free ( evcon ) ;
 evhttp_free ( http ) ;
 fprintf ( stdout , "OK\n" ) ;
 }