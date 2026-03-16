static void nameserver_failed ( struct nameserver * const ns , const char * msg ) {
 struct request * req , * started_at ;
 if ( ! ns -> state ) return ;
 log ( EVDNS_LOG_WARN , "Nameserver %s has failed: %s" , debug_ntoa ( ns -> address ) , msg ) ;
 global_good_nameservers -- ;
 assert ( global_good_nameservers >= 0 ) ;
 if ( global_good_nameservers == 0 ) {
 log ( EVDNS_LOG_WARN , "All nameservers have failed" ) ;
 }
 ns -> state = 0 ;
 ns -> failed_times = 1 ;
 if ( evtimer_add ( & ns -> timeout_event , ( struct timeval * ) & global_nameserver_timeouts [ 0 ] ) < 0 ) {
 log ( EVDNS_LOG_WARN , "Error from libevent when adding timer event for %s" , debug_ntoa ( ns -> address ) ) ;
 }
 if ( ! global_good_nameservers ) return ;
 req = req_head ;
 started_at = req_head ;
 if ( req ) {
 do {
 if ( req -> tx_count == 0 && req -> ns == ns ) {
 req -> ns = nameserver_pick ( ) ;
 }
 req = req -> next ;
 }
 while ( req != started_at ) ;
 }
 }