void http_request_empty_done ( struct evhttp_request * req , void * arg ) {
 if ( req -> response_code != HTTP_OK ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( evhttp_find_header ( req -> input_headers , "Date" ) == NULL ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( evhttp_find_header ( req -> input_headers , "Content-Length" ) == NULL ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( strcmp ( evhttp_find_header ( req -> input_headers , "Content-Length" ) , "0" ) ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( EVBUFFER_LENGTH ( req -> input_buffer ) != 0 ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 test_ok = 1 ;
 event_loopexit ( NULL ) ;
 }