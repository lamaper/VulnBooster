static void evdns_request_timeout_callback ( int fd , short events , void * arg ) {
 struct request * const req = ( struct request * ) arg ;
 ( void ) fd ;
 ( void ) events ;
 log ( EVDNS_LOG_DEBUG , "Request %lx timed out" , ( unsigned long ) arg ) ;
 req -> ns -> timedout ++ ;
 if ( req -> ns -> timedout > global_max_nameserver_timeout ) {
 req -> ns -> timedout = 0 ;
 nameserver_failed ( req -> ns , "request timed out." ) ;
 }
 ( void ) evtimer_del ( & req -> timeout_event ) ;
 if ( req -> tx_count >= global_max_retransmits ) {
 reply_callback ( req , 0 , DNS_ERR_TIMEOUT , NULL ) ;
 request_finished ( req , & req_head ) ;
 }
 else {
 evdns_request_transmit ( req ) ;
 }
 }