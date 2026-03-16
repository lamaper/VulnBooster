static inline void evhttp_send ( struct evhttp_request * req , struct evbuffer * databuf ) {
 struct evhttp_connection * evcon = req -> evcon ;
 assert ( TAILQ_FIRST ( & evcon -> requests ) == req ) ;
 if ( databuf != NULL ) evbuffer_add_buffer ( req -> output_buffer , databuf ) ;
 evhttp_make_header ( evcon , req ) ;
 evhttp_write_buffer ( evcon , evhttp_send_done , NULL ) ;
 }