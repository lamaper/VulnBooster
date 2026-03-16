static void http_chunked_cb ( struct evhttp_request * req , void * arg ) {
 struct timeval when = {
 0 , 0 }
 ;
 struct chunk_req_state * state = malloc ( sizeof ( struct chunk_req_state ) ) ;
 event_debug ( ( "%s: called\n" , __func__ ) ) ;
 memset ( state , 0 , sizeof ( struct chunk_req_state ) ) ;
 state -> req = req ;
 evhttp_send_reply_start ( req , HTTP_OK , "Everything is fine" ) ;
 event_once ( - 1 , EV_TIMEOUT , http_chunked_trickle_cb , state , & when ) ;
 }