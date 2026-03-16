static void http_close_detection ( int with_delay ) {
 short port = - 1 ;
 struct evhttp_connection * evcon = NULL ;
 struct evhttp_request * req = NULL ;
 test_ok = 0 ;
 fprintf ( stdout , "Testing Connection Close Detection%s: " , with_delay ? " (with delay)" : "" ) ;
 http = http_setup ( & port , NULL ) ;
 evhttp_set_timeout ( http , 2 ) ;
 evcon = evhttp_connection_new ( "127.0.0.1" , port ) ;
 if ( evcon == NULL ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 delayed_client = evcon ;
 req = evhttp_request_new ( close_detect_cb , evcon ) ;
 evhttp_add_header ( req -> output_headers , "Host" , "somehost" ) ;
 if ( evhttp_make_request ( evcon , req , EVHTTP_REQ_GET , with_delay ? "/largedelay" : "/test" ) == - 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 event_dispatch ( ) ;
 if ( test_ok != 1 ) {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( TAILQ_FIRST ( & http -> connections ) != NULL ) {
 fprintf ( stdout , "FAILED (left connections)\n" ) ;
 exit ( 1 ) ;
 }
 evhttp_connection_free ( evcon ) ;
 evhttp_free ( http ) ;
 fprintf ( stdout , "OK\n" ) ;
 }