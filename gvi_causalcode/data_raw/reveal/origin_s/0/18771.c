static u16 transaction_id_pick ( void ) {
 for ( ;
 ;
 ) {
 u16 trans_id = trans_id_function ( ) ;
 if ( trans_id == 0xffff ) continue ;
 if ( request_find_from_trans_id ( trans_id ) == NULL ) return trans_id ;
 }
 }