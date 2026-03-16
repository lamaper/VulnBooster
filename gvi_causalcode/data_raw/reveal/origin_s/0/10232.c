static int vvalue_tvb_lpwstr ( tvbuff_t * tvb , int offset , void * val ) {
 struct data_str * str = ( struct data_str * ) val ;
 str -> len = tvb_get_letohl ( tvb , offset ) ;
 return 4 + vvalue_tvb_lpwstr_len ( tvb , offset + 4 , 0 , val ) ;
 }