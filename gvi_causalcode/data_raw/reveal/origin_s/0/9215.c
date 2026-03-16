static void http_dispatcher_test ( void ) {
 short port = - 1 ;
 struct evhttp_connection * evcon = NULL ;
 struct evhttp_request * req = NULL ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing HTTP Dispatcher: " ) ;
 http = http_setup ( & port , NULL ) ;
 evcon = evhttp_connection_new ( "127.0.0.1" , port ) ;
 if ( evcon == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 evhttp_connection_set_local_address ( evcon , "127.0.0.1" ) ;
 req = evhttp_request_new ( http_dispatcher_test_done , NULL ) ;
 if ( req == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/?arg=val" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 evhttp_connection_free ( evcon ) ;
 evhttp_free ( http ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED: %d\n" , test_ok ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }