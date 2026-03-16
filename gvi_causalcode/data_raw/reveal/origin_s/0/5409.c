static int evdns_request_transmit ( struct request * req ) {
 int retcode = 0 , r ;
 req -> transmit_me = 1 ;
 if ( req -> trans_id == 0xffff ) abort ( ) ;
 if ( req -> ns -> choked ) {
 return 1 ;
 }
 r = evdns_request_transmit_to ( req , req -> ns ) ;
 switch ( r ) {
 case 1 : req -> ns -> choked = 1 ;
 nameserver_write_waiting ( req -> ns , 1 ) ;
 return 1 ;
 case 2 : retcode = 1 ;
 default : log ( EVDNS_LOG_DEBUG , "Setting timeout for request %lx" , ( unsigned long ) req ) ;
 if ( evtimer_add ( & req -> timeout_event , & global_timeout ) < 0 ) {
 log ( EVDNS_LOG_WARN , "Error from libevent when adding timer for request %lx" , ( unsigned long ) req ) ;
 }
 req -> tx_count ++ ;
 req -> transmit_me = 0 ;
 return retcode ;
 }
 }