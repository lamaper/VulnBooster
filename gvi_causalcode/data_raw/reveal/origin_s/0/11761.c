static gint nlm_msg_res_unmatched_equal ( gconstpointer k1 , gconstpointer k2 ) {
 const nlm_msg_res_unmatched_data * umd1 = ( const nlm_msg_res_unmatched_data * ) k1 ;
 const nlm_msg_res_unmatched_data * umd2 = ( const nlm_msg_res_unmatched_data * ) k2 ;
 if ( umd1 -> cookie_len != umd2 -> cookie_len ) {
 return 0 ;
 }
 return ( memcmp ( umd1 -> cookie , umd2 -> cookie , umd1 -> cookie_len ) == 0 ) ;
 }