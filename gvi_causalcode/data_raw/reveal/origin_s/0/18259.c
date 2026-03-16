static void http_chunked_trickle_cb ( int fd , short events , void * arg ) {
 struct evbuffer * evb = evbuffer_new ( ) ;
 struct chunk_req_state * state = arg ;
 struct timeval when = {
 0 , 0 }
 ;
 evbuffer_add_printf ( evb , "%s" , CHUNKS [ state -> i ] ) ;
 evhttp_send_reply_chunk ( state -> req , evb ) ;
 evbuffer_free ( evb ) ;
 if ( ++ state -> i < sizeof ( CHUNKS ) / sizeof ( CHUNKS [ 0 ] ) ) {
 event_once ( - 1 , EV_TIMEOUT , http_chunked_trickle_cb , state , & when ) ;
 }
 else {
 evhttp_send_reply_end ( state -> req ) ;
 free ( state ) ;
 }
 }