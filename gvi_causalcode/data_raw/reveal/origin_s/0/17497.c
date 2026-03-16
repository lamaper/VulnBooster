static void terminate_chunked_cb ( struct evhttp_request * req , void * arg ) {
 struct terminate_state * state = arg ;
 struct timeval tv ;
 state -> req = req ;
 evhttp_send_reply_start ( req , HTTP_OK , "OK" ) ;
 tv . tv_sec = 0 ;
 tv . tv_usec = 3000 ;
 event_once ( - 1 , EV_TIMEOUT , terminate_chunked_trickle_cb , arg , & tv ) ;
 }