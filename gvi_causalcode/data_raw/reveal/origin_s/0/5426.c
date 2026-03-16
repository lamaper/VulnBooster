static void evhttp_request_dispatch ( struct evhttp_connection * evcon ) {
 struct evhttp_request * req = TAILQ_FIRST ( & evcon -> requests ) ;
 if ( req == NULL ) return ;
 evhttp_connection_stop_detectclose ( evcon ) ;
 assert ( evcon -> state == EVCON_IDLE ) ;
 evcon -> state = EVCON_WRITING ;
 evhttp_make_header ( evcon , req ) ;
 evhttp_write_buffer ( evcon , evhttp_write_connectioncb , NULL ) ;
 }