static void evdns_requests_pump_waiting_queue ( void ) {
 while ( global_requests_inflight < global_max_requests_inflight && global_requests_waiting ) {
 struct request * req ;
 assert ( req_waiting_head ) ;
 if ( req_waiting_head -> next == req_waiting_head ) {
 req = req_waiting_head ;
 req_waiting_head = NULL ;
 }
 else {
 req = req_waiting_head ;
 req -> next -> prev = req -> prev ;
 req -> prev -> next = req -> next ;
 req_waiting_head = req -> next ;
 }
 global_requests_waiting -- ;
 global_requests_inflight ++ ;
 req -> ns = nameserver_pick ( ) ;
 request_trans_id_set ( req , transaction_id_pick ( ) ) ;
 evdns_request_insert ( req , & req_head ) ;
 evdns_request_transmit ( req ) ;
 evdns_transmit ( ) ;
 }
 }