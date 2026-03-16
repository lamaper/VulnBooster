void evhttp_response_code ( struct evhttp_request * req , int code , const char * reason ) {
 req -> kind = EVHTTP_RESPONSE ;
 req -> response_code = code ;
 if ( req -> response_code_line != NULL ) free ( req -> response_code_line ) ;
 req -> response_code_line = strdup ( reason ) ;
 }