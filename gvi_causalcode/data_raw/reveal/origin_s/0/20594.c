static void evhttp_write_connectioncb ( struct evhttp_connection * evcon , void * arg ) {
 struct evhttp_request * req = TAILQ_FIRST ( & evcon -> requests ) ;
 assert ( req != NULL ) ;
 assert ( evcon -> state == EVCON_WRITING ) ;
 req -> kind = EVHTTP_RESPONSE ;
 evhttp_start_read ( evcon ) ;
 }