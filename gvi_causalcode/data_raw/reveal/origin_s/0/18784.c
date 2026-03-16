int evdns_clear_nameservers_and_suspend ( void ) {
 struct nameserver * server = server_head , * started_at = server_head ;
 struct request * req = req_head , * req_started_at = req_head ;
 if ( ! server ) return 0 ;
 while ( 1 ) {
 struct nameserver * next = server -> next ;
 ( void ) event_del ( & server -> event ) ;
 if ( evtimer_initialized ( & server -> timeout_event ) ) ( void ) evtimer_del ( & server -> timeout_event ) ;
 if ( server -> socket >= 0 ) CLOSE_SOCKET ( server -> socket ) ;
 free ( server ) ;
 if ( next == started_at ) break ;
 server = next ;
 }
 server_head = NULL ;
 global_good_nameservers = 0 ;
 while ( req ) {
 struct request * next = req -> next ;
 req -> tx_count = req -> reissue_count = 0 ;
 req -> ns = NULL ;
 ( void ) evtimer_del ( & req -> timeout_event ) ;
 req -> trans_id = 0 ;
 req -> transmit_me = 0 ;
 global_requests_waiting ++ ;
 evdns_request_insert ( req , & req_waiting_head ) ;
 req_waiting_head = req_waiting_head -> prev ;
 if ( next == req_started_at ) break ;
 req = next ;
 }
 req_head = NULL ;
 global_requests_inflight = 0 ;
 return 0 ;
 }