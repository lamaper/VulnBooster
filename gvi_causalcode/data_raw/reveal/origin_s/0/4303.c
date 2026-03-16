void http_basic_cb ( struct evhttp_request * req , void * arg ) {
 struct evbuffer * evb = evbuffer_new ( ) ;
 int empty = evhttp_find_header ( req -> input_headers , "Empty" ) != NULL ;
 event_debug ( ( "%s: called\n" , __func__ ) ) ;
 evbuffer_add_printf ( evb , "This is funny" ) ;
 {
 const char * multi = evhttp_find_header ( req -> input_headers , "X-multi" ) ;
 if ( multi ) {
 if ( strcmp ( "END" , multi + strlen ( multi ) - 3 ) == 0 ) test_ok ++ ;
 if ( evhttp_find_header ( req -> input_headers , "X-Last" ) ) test_ok ++ ;
 }
 }
 if ( evhttp_find_header ( req -> input_headers , "X-Negative" ) ) evhttp_add_header ( req -> output_headers , "Content-Length" , "-100" ) ;
 evhttp_send_reply ( req , HTTP_OK , "Everything is fine" , ! empty ? evb : NULL ) ;
 evbuffer_free ( evb ) ;
 }