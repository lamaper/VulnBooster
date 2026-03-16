void http_dispatcher_cb ( struct evhttp_request * req , void * arg ) {
 struct evbuffer * evb = evbuffer_new ( ) ;
 event_debug ( ( "%s: called\n" , __func__ ) ) ;
 evbuffer_add_printf ( evb , "DISPATCHER_TEST" ) ;
 evhttp_send_reply ( req , HTTP_OK , "Everything is fine" , evb ) ;
 evbuffer_free ( evb ) ;
 }