static inline void evhttp_send ( struct evhttp_request * req , struct evbuffer * databuf ) {
 struct evhttp_connection * evcon = req -> evcon ;
 if ( evcon == NULL ) {
 evhttp_request_free ( req ) ;
 return ;
 }
 assert ( TAILQ_FIRST ( & evcon -> requests ) == req ) ;
 req -> userdone = 1 ;
 if ( databuf != NULL ) evbuffer_add_buffer ( req -> output_buffer , databuf ) ;
 evhttp_make_header ( evcon , req ) ;
 evhttp_write_buffer ( evcon , evhttp_send_done , NULL ) ;
 }