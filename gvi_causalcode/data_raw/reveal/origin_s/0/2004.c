void evhttp_request_free ( struct evhttp_request * req ) {
 if ( req -> remote_host != NULL ) free ( req -> remote_host ) ;
 if ( req -> uri != NULL ) free ( req -> uri ) ;
 if ( req -> response_code_line != NULL ) free ( req -> response_code_line ) ;
 evhttp_clear_headers ( req -> input_headers ) ;
 free ( req -> input_headers ) ;
 evhttp_clear_headers ( req -> output_headers ) ;
 free ( req -> output_headers ) ;
 if ( req -> input_buffer != NULL ) evbuffer_free ( req -> input_buffer ) ;
 if ( req -> output_buffer != NULL ) evbuffer_free ( req -> output_buffer ) ;
 free ( req ) ;
 }