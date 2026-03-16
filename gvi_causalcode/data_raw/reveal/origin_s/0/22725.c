static void http_badreq_cb ( struct evhttp_request * req , void * arg ) {
 struct evbuffer * buf = evbuffer_new ( ) ;
 evhttp_add_header ( req -> output_headers , "Content-Type" , "text/xml;
 charset=UTF-8" ) ;
 evbuffer_add_printf ( buf , "Hello, %s!" , "127.0.0.1" ) ;
 evhttp_send_reply ( req , HTTP_OK , "OK" , buf ) ;
 evbuffer_free ( buf ) ;
 }