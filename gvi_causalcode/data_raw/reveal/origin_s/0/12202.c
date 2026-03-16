static int32_t u_sprintf_write ( void * context , const UChar * str , int32_t count ) {
 u_localized_print_string * output = ( u_localized_print_string * ) context ;
 int32_t size = ufmt_min ( count , output -> available ) ;
 u_strncpy ( output -> str + ( output -> len - output -> available ) , str , size ) ;
 output -> available -= size ;
 return size ;
 }