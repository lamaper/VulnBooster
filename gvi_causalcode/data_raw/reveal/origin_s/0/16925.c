struct evhttp_request * evhttp_request_new ( void ( * cb ) ( struct evhttp_request * , void * ) , void * arg ) {
 struct evhttp_request * req = NULL ;
 if ( ( req = calloc ( 1 , sizeof ( struct evhttp_request ) ) ) == NULL ) {
 event_warn ( "%s: calloc" , __func__ ) ;
 goto error ;
 }
 req -> kind = EVHTTP_RESPONSE ;
 req -> input_headers = calloc ( 1 , sizeof ( struct evkeyvalq ) ) ;
 if ( req -> input_headers == NULL ) {
 event_warn ( "%s: calloc" , __func__ ) ;
 goto error ;
 }
 TAILQ_INIT ( req -> input_headers ) ;
 req -> output_headers = calloc ( 1 , sizeof ( struct evkeyvalq ) ) ;
 if ( req -> output_headers == NULL ) {
 event_warn ( "%s: calloc" , __func__ ) ;
 goto error ;
 }
 TAILQ_INIT ( req -> output_headers ) ;
 if ( ( req -> input_buffer = evbuffer_new ( ) ) == NULL ) {
 event_warn ( "%s: evbuffer_new" , __func__ ) ;
 goto error ;
 }
 if ( ( req -> output_buffer = evbuffer_new ( ) ) == NULL ) {
 event_warn ( "%s: evbuffer_new" , __func__ ) ;
 goto error ;
 }
 req -> cb = cb ;
 req -> cb_arg = arg ;
 return ( req ) ;
 error : if ( req != NULL ) evhttp_request_free ( req ) ;
 return ( NULL ) ;
 }