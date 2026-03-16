int evdns_resume ( void ) {
 evdns_requests_pump_waiting_queue ( ) ;
 return 0 ;
 }