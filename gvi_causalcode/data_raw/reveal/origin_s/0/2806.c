static void evdns_request_insert ( struct request * req , struct request * * head ) {
 if ( ! * head ) {
 * head = req ;
 req -> next = req -> prev = req ;
 return ;
 }
 req -> prev = ( * head ) -> prev ;
 req -> prev -> next = req ;
 req -> next = * head ;
 ( * head ) -> prev = req ;
 }