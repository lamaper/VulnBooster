static enum message_read_status evhttp_handle_chunked_read ( struct evhttp_request * req , struct evbuffer * buf ) {
 int len ;
 while ( ( len = EVBUFFER_LENGTH ( buf ) ) > 0 ) {
 if ( req -> ntoread < 0 ) {
 ev_int64_t ntoread ;
 char * p = evbuffer_readline ( buf ) ;
 char * endp ;
 int error ;
 if ( p == NULL ) break ;
 if ( strlen ( p ) == 0 ) {
 free ( p ) ;
 continue ;
 }
 ntoread = evutil_strtoll ( p , & endp , 16 ) ;
 error = ( * p == '\0' || ( * endp != '\0' && * endp != ' ' ) || ntoread < 0 ) ;
 free ( p ) ;
 if ( error ) {
 return ( DATA_CORRUPTED ) ;
 }
 req -> ntoread = ntoread ;
 if ( req -> ntoread == 0 ) {
 return ( ALL_DATA_READ ) ;
 }
 continue ;
 }
 if ( len < req -> ntoread ) return ( MORE_DATA_EXPECTED ) ;
 evbuffer_add ( req -> input_buffer , EVBUFFER_DATA ( buf ) , ( size_t ) req -> ntoread ) ;
 evbuffer_drain ( buf , ( size_t ) req -> ntoread ) ;
 req -> ntoread = - 1 ;
 if ( req -> chunk_cb != NULL ) {
 ( * req -> chunk_cb ) ( req , req -> cb_arg ) ;
 evbuffer_drain ( req -> input_buffer , EVBUFFER_LENGTH ( req -> input_buffer ) ) ;
 }
 }
 return ( MORE_DATA_EXPECTED ) ;
 }