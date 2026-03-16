static void evhttp_make_header_response ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 int is_keepalive = evhttp_is_connection_keepalive ( req -> input_headers ) ;
 evbuffer_add_printf ( evcon -> output_buffer , "HTTP/%d.%d %d %s\r\n" , req -> major , req -> minor , req -> response_code , req -> response_code_line ) ;
 if ( req -> major == 1 ) {
 if ( req -> minor == 1 ) evhttp_maybe_add_date_header ( req -> output_headers ) ;
 if ( req -> minor == 0 && is_keepalive ) evhttp_add_header ( req -> output_headers , "Connection" , "keep-alive" ) ;
 if ( req -> minor == 1 || is_keepalive ) {
 evhttp_maybe_add_content_length_header ( req -> output_headers , ( long ) EVBUFFER_LENGTH ( req -> output_buffer ) ) ;
 }
 }
 if ( EVBUFFER_LENGTH ( req -> output_buffer ) ) {
 if ( evhttp_find_header ( req -> output_headers , "Content-Type" ) == NULL ) {
 evhttp_add_header ( req -> output_headers , "Content-Type" , "text/html;
 charset=ISO-8859-1" ) ;
 }
 }
 if ( evhttp_is_connection_close ( req -> flags , req -> input_headers ) ) {
 evhttp_remove_header ( req -> output_headers , "Connection" ) ;
 if ( ! ( req -> flags & EVHTTP_PROXY_REQUEST ) ) evhttp_add_header ( req -> output_headers , "Connection" , "close" ) ;
 evhttp_remove_header ( req -> output_headers , "Proxy-Connection" ) ;
 }
 }