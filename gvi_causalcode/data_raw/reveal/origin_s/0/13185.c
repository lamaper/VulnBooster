static void http_post_test ( void ) {
 short port = - 1 ;
 struct evhttp_connection * evcon = NULL ;
 struct evhttp_request * req = NULL ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing HTTP POST Request: " ) ;
 http = http_setup ( & port , NULL ) ;
 evcon = evhttp_connection_new ( "127.0.0.1" , port ) ;
 if ( evcon == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 req = evhttp_request_new ( http_postrequest_done , NULL ) ;
 if ( req == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 evbuffer_add_printf ( req -> output_buffer , POST_DATA ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_POST , "/postit" ) == - 1 ) {
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