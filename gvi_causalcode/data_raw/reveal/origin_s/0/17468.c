void evhttp_send_reply_end ( struct evhttp_request * req ) {
 struct evhttp_connection * evcon = req -> evcon ;
 if ( evcon == NULL ) {
 evhttp_request_free ( req ) ;
 return ;
 }
 req -> userdone = 1 ;
 if ( req -> chunked ) {
 evbuffer_add ( req -> evcon -> output_buffer , "0\r\n\r\n" , 5 ) ;
 evhttp_write_buffer ( req -> evcon , evhttp_send_done , NULL ) ;
 req -> chunked = 0 ;
 }
 else if ( ! event_pending ( & evcon -> ev , EV_WRITE | EV_TIMEOUT , NULL ) ) {
 evhttp_send_done ( evcon , NULL ) ;
 }
 else {
 evcon -> cb = evhttp_send_done ;
 evcon -> cb_arg = NULL ;
 }
 }