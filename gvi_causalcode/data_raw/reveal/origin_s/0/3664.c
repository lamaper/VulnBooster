void evhttp_send_reply_start ( struct evhttp_request * req , int code , const char * reason ) {
 evhttp_response_code ( req , code , reason ) ;
 if ( req -> major == 1 && req -> minor == 1 ) {
 evhttp_add_header ( req -> output_headers , "Transfer-Encoding" , "chunked" ) ;
 req -> chunked = 1 ;
 }
 evhttp_make_header ( req -> evcon , req ) ;
 evhttp_write_buffer ( req -> evcon , NULL , NULL ) ;
 }