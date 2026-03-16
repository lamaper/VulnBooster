static int32_t get_send_time ( ASFContext * asf , int64_t pres_time , uint64_t * offset ) {
 int i ;
 int32_t send_time = 0 ;
 * offset = asf -> data_offset + DATA_HEADER_SIZE ;
 for ( i = 0 ;
 i < asf -> next_start_sec ;
 i ++ ) {
 if ( pres_time <= asf -> index_ptr [ i ] . send_time ) break ;
 send_time = asf -> index_ptr [ i ] . send_time ;
 * offset = asf -> index_ptr [ i ] . offset ;
 }
 return send_time / 10000 ;
 }