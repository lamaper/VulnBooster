static void http_chunked_request_done ( struct evhttp_request * req , void * arg ) {
 if ( req -> response_code != HTTP_OK ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( evhttp_find_header ( req -> input_headers , "Transfer-Encoding" ) == NULL ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( EVBUFFER_LENGTH ( req -> input_buffer ) != 13 + 18 + 8 ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 if ( strncmp ( ( char * ) EVBUFFER_DATA ( req -> input_buffer ) , "This is funnybut not hilarious.bwv 1052" , + 18 + 8 ) ) {
 fprintf ( stderr , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 test_ok = 1 ;
 event_loopexit ( NULL ) ;
 }