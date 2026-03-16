void evhttp_make_header ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 struct evkeyval * header ;
 if ( req -> kind == EVHTTP_REQUEST ) {
 evhttp_make_header_request ( evcon , req ) ;
 }
 else {
 evhttp_make_header_response ( evcon , req ) ;
 }
 TAILQ_FOREACH ( header , req -> output_headers , next ) {
 evbuffer_add_printf ( evcon -> output_buffer , "%s: %s\r\n" , header -> key , header -> value ) ;
 }
 evbuffer_add ( evcon -> output_buffer , "\r\n" , 2 ) ;
 if ( EVBUFFER_LENGTH ( req -> output_buffer ) > 0 ) {
 evbuffer_add_buffer ( evcon -> output_buffer , req -> output_buffer ) ;
 }
 }