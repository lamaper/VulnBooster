h225ras_call_t * find_h225ras_call ( h225ras_call_info_key * h225ras_call_key , int category ) {
 h225ras_call_t * h225ras_call = NULL ;
 h225ras_call = ( h225ras_call_t * ) g_hash_table_lookup ( ras_calls [ category ] , h225ras_call_key ) ;
 return h225ras_call ;
 }