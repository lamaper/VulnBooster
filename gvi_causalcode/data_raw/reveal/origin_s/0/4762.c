static int evdns_transmit ( void ) {
 char did_try_to_transmit = 0 ;
 if ( req_head ) {
 struct request * const started_at = req_head , * req = req_head ;
 do {
 if ( req -> transmit_me ) {
 did_try_to_transmit = 1 ;
 evdns_request_transmit ( req ) ;
 }
 req = req -> next ;
 }
 while ( req != started_at ) ;
 }
 return did_try_to_transmit ;
 }