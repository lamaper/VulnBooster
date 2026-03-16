static guint nlm_msg_res_unmatched_hash ( gconstpointer k ) {
 const nlm_msg_res_unmatched_data * umd = ( const nlm_msg_res_unmatched_data * ) k ;
 guint8 hash = 0 ;
 int i ;
 for ( i = 0 ;
 i < umd -> cookie_len ;
 i ++ ) {
 hash ^= umd -> cookie [ i ] ;
 }
 return hash ;
 }