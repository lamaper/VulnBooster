static void http_negative_content_length_test ( void ) {
 short port = - 1 ;
 struct evhttp_connection * evcon = NULL ;
 struct evhttp_request * req = NULL ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing HTTP Negative Content Length: " ) ;
 http = http_setup ( & port , NULL ) ;
 evcon = evhttp_connection_new ( "127.0.0.1" , port ) ;
 if ( evcon == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 req = evhttp_request_new ( http_request_bad , NULL ) ;
 evhttp_add_header ( req -> output_headers , "X-Negative" , "makeitso" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , "/test" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 evhttp_free ( http ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 fprintf ( stdout , "OK\n" ) ;
 }