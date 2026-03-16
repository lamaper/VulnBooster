void evdns_shutdown ( int fail_requests ) {
 struct nameserver * server , * server_next ;
 struct search_domain * dom , * dom_next ;
 while ( req_head ) {
 if ( fail_requests ) reply_callback ( req_head , 0 , DNS_ERR_SHUTDOWN , NULL ) ;
 request_finished ( req_head , & req_head ) ;
 }
 while ( req_waiting_head ) {
 if ( fail_requests ) reply_callback ( req_waiting_head , 0 , DNS_ERR_SHUTDOWN , NULL ) ;
 request_finished ( req_waiting_head , & req_waiting_head ) ;
 }
 global_requests_inflight = global_requests_waiting = 0 ;
 for ( server = server_head ;
 server ;
 server = server_next ) {
 server_next = server -> next ;
 if ( server -> socket >= 0 ) CLOSE_SOCKET ( server -> socket ) ;
 ( void ) event_del ( & server -> event ) ;
 if ( server -> state == 0 ) ( void ) event_del ( & server -> timeout_event ) ;
 free ( server ) ;
 if ( server_next == server_head ) break ;
 }
 server_head = NULL ;
 global_good_nameservers = 0 ;
 if ( global_search_state ) {
 for ( dom = global_search_state -> head ;
 dom ;
 dom = dom_next ) {
 dom_next = dom -> next ;
 free ( dom ) ;
 }
 free ( global_search_state ) ;
 global_search_state = NULL ;
 }
 evdns_log_fn = NULL ;
 }