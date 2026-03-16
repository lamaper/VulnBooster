struct evhttp_connection * evhttp_connection_new ( const char * address , unsigned short port ) {
 struct evhttp_connection * evcon = NULL ;
 event_debug ( ( "Attempting connection to %s:%d\n" , address , port ) ) ;
 if ( ( evcon = calloc ( 1 , sizeof ( struct evhttp_connection ) ) ) == NULL ) {
 event_warn ( "%s: calloc failed" , __func__ ) ;
 goto error ;
 }
 evcon -> fd = - 1 ;
 evcon -> port = port ;
 evcon -> timeout = - 1 ;
 evcon -> retry_cnt = evcon -> retry_max = 0 ;
 if ( ( evcon -> address = strdup ( address ) ) == NULL ) {
 event_warn ( "%s: strdup failed" , __func__ ) ;
 goto error ;
 }
 if ( ( evcon -> input_buffer = evbuffer_new ( ) ) == NULL ) {
 event_warn ( "%s: evbuffer_new failed" , __func__ ) ;
 goto error ;
 }
 if ( ( evcon -> output_buffer = evbuffer_new ( ) ) == NULL ) {
 event_warn ( "%s: evbuffer_new failed" , __func__ ) ;
 goto error ;
 }
 evcon -> state = EVCON_DISCONNECTED ;
 TAILQ_INIT ( & evcon -> requests ) ;
 return ( evcon ) ;
 error : if ( evcon != NULL ) evhttp_connection_free ( evcon ) ;
 return ( NULL ) ;
 }