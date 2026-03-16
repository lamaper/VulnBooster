static void request_finished ( struct request * const req , struct request * * head ) {
 if ( head ) {
 if ( req -> next == req ) {
 * head = NULL ;
 }
 else {
 req -> next -> prev = req -> prev ;
 req -> prev -> next = req -> next ;
 if ( * head == req ) * head = req -> next ;
 }
 }
 log ( EVDNS_LOG_DEBUG , "Removing timeout for request %lx" , ( unsigned long ) req ) ;
 evtimer_del ( & req -> timeout_event ) ;
 search_request_finished ( req ) ;
 global_requests_inflight -- ;
 if ( ! req -> request_appended ) {
 free ( req -> request ) ;
 }
 else {
 }
 free ( req ) ;
 evdns_requests_pump_waiting_queue ( ) ;
 }