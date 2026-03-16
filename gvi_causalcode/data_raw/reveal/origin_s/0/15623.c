static void evhttp_get_body ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 const char * xfer_enc ;
 if ( req -> kind == EVHTTP_REQUEST && req -> type != EVHTTP_REQ_POST ) {
 evhttp_connection_done ( evcon ) ;
 return ;
 }
 evcon -> state = EVCON_READING_BODY ;
 xfer_enc = evhttp_find_header ( req -> input_headers , "Transfer-Encoding" ) ;
 if ( xfer_enc != NULL && strcasecmp ( xfer_enc , "chunked" ) == 0 ) {
 req -> chunked = 1 ;
 req -> ntoread = - 1 ;
 }
 else {
 if ( evhttp_get_body_length ( req ) == - 1 ) {
 evhttp_connection_fail ( evcon , EVCON_HTTP_INVALID_HEADER ) ;
 return ;
 }
 }
 evhttp_read_body ( evcon , req ) ;
 }