static struct request * request_find_from_trans_id ( u16 trans_id ) {
 struct request * req = req_head , * const started_at = req_head ;
 if ( req ) {
 do {
 if ( req -> trans_id == trans_id ) return req ;
 req = req -> next ;
 }
 while ( req != started_at ) ;
 }
 return NULL ;
 }