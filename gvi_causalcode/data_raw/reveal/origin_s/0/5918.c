static int server_request_free ( struct server_request * req ) {
 int i , rc = 1 ;
 if ( req -> base . questions ) {
 for ( i = 0 ;
 i < req -> base . nquestions ;
 ++ i ) free ( req -> base . questions [ i ] ) ;
 free ( req -> base . questions ) ;
 }
 if ( req -> port ) {
 if ( req -> port -> pending_replies == req ) {
 if ( req -> next_pending ) req -> port -> pending_replies = req -> next_pending ;
 else req -> port -> pending_replies = NULL ;
 }
 rc = -- req -> port -> refcnt ;
 }
 if ( req -> response ) {
 free ( req -> response ) ;
 }
 server_request_free_answers ( req ) ;
 if ( req -> next_pending && req -> next_pending != req ) {
 req -> next_pending -> prev_pending = req -> prev_pending ;
 req -> prev_pending -> next_pending = req -> next_pending ;
 }
 if ( rc == 0 ) {
 server_port_free ( req -> port ) ;
 free ( req ) ;
 return ( 1 ) ;
 }
 free ( req ) ;
 return ( 0 ) ;
 }