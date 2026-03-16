static void request_submit ( struct request * const req ) {
 if ( req -> ns ) {
 evdns_request_insert ( req , & req_head ) ;
 global_requests_inflight ++ ;
 evdns_request_transmit ( req ) ;
 }
 else {
 evdns_request_insert ( req , & req_waiting_head ) ;
 global_requests_waiting ++ ;
 }
 }