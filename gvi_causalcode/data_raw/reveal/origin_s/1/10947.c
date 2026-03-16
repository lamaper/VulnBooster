static u16 transaction_id_pick ( void ) {
 for ( ;
 ;
 ) {
 const struct request * req = req_head , * started_at ;
 u16 trans_id = trans_id_function ( ) ;
 if ( trans_id == 0xffff ) continue ;
 req = started_at = req_head ;
 if ( req ) {
 do {
 if ( req -> trans_id == trans_id ) break ;
 req = req -> next ;
 }
 while ( req != started_at ) ;
 }
 if ( req == started_at ) return trans_id ;
 }
 }