enum message_read_status evhttp_parse_firstline ( struct evhttp_request * req , struct evbuffer * buffer ) {
 char * line ;
 enum message_read_status status = ALL_DATA_READ ;
 line = evbuffer_readline ( buffer ) ;
 if ( line == NULL ) return ( MORE_DATA_EXPECTED ) ;
 switch ( req -> kind ) {
 case EVHTTP_REQUEST : if ( evhttp_parse_request_line ( req , line ) == - 1 ) status = DATA_CORRUPTED ;
 break ;
 case EVHTTP_RESPONSE : if ( evhttp_parse_response_line ( req , line ) == - 1 ) status = DATA_CORRUPTED ;
 break ;
 default : status = DATA_CORRUPTED ;
 }
 free ( line ) ;
 return ( status ) ;
 }