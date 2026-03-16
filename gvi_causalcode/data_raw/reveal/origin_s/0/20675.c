static int evhttp_get_body_length ( struct evhttp_request * req ) {
 struct evkeyvalq * headers = req -> input_headers ;
 const char * content_length ;
 const char * connection ;
 content_length = evhttp_find_header ( headers , "Content-Length" ) ;
 connection = evhttp_find_header ( headers , "Connection" ) ;
 if ( content_length == NULL && connection == NULL ) req -> ntoread = - 1 ;
 else if ( content_length == NULL && strcasecmp ( connection , "Close" ) != 0 ) {
 event_warnx ( "%s: we got no content length, but the " "server wants to keep the connection open: %s." , __func__ , connection ) ;
 return ( - 1 ) ;
 }
 else if ( content_length == NULL ) {
 req -> ntoread = - 1 ;
 }
 else {
 char * endp ;
 ev_int64_t ntoread = evutil_strtoll ( content_length , & endp , 10 ) ;
 if ( * content_length == '\0' || * endp != '\0' || ntoread < 0 ) {
 event_debug ( ( "%s: illegal content length: %s" , __func__ , content_length ) ) ;
 return ( - 1 ) ;
 }
 req -> ntoread = ntoread ;
 }
 event_debug ( ( "%s: bytes to read: %lld (in buffer %ld)\n" , __func__ , req -> ntoread , EVBUFFER_LENGTH ( req -> evcon -> input_buffer ) ) ) ;
 return ( 0 ) ;
 }