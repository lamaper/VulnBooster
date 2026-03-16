int64_t ufmt_uto64 ( const UChar * buffer , int32_t * len , int8_t radix ) {
 const UChar * limit ;
 int32_t count ;
 int64_t result ;
 limit = buffer + * len ;
 count = 0 ;
 result = 0 ;
 while ( ufmt_isdigit ( * buffer , radix ) && buffer < limit ) {
 result *= radix ;
 result += ufmt_digitvalue ( * buffer ++ ) ;
 ++ count ;
 }
 * len = count ;
 return result ;
 }