static void http_large_delay_cb ( struct evhttp_request * req , void * arg ) {
 struct timeval tv ;
 timerclear ( & tv ) ;
 tv . tv_sec = 3 ;
 event_once ( - 1 , EV_TIMEOUT , http_delay_reply , req , & tv ) ;
 evhttp_connection_fail ( delayed_client , EVCON_HTTP_EOF ) ;
 }