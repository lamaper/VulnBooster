static void terminate_chunked_trickle_cb ( int fd , short events , void * arg ) {
 struct terminate_state * state = arg ;
 struct evbuffer * evb = evbuffer_new ( ) ;
 struct timeval tv ;
 if ( evhttp_request_get_connection ( state -> req ) == NULL ) {
 test_ok = 1 ;
 evhttp_request_free ( state -> req ) ;
 event_loopexit ( NULL ) ;
 return ;
 }
 evbuffer_add_printf ( evb , "%p" , evb ) ;
 evhttp_send_reply_chunk ( state -> req , evb ) ;
 evbuffer_free ( evb ) ;
 tv . tv_sec = 0 ;
 tv . tv_usec = 3000 ;
 event_once ( - 1 , EV_TIMEOUT , terminate_chunked_trickle_cb , arg , & tv ) ;
 }