static uint64_t ar_atol8 ( const char * p , unsigned char_cnt ) {
 uint64_t l , limit , last_digit_limit ;
 unsigned int digit , base ;
 base = 8 ;
 limit = UINT64_MAX / base ;
 last_digit_limit = UINT64_MAX % base ;
 while ( ( * p == ' ' || * p == '\t' ) && char_cnt -- > 0 ) p ++ ;
 l = 0 ;
 digit = * p - '0' ;
 while ( * p >= '0' && digit < base && char_cnt -- > 0 ) {
 if ( l > limit || ( l == limit && digit > last_digit_limit ) ) {
 l = UINT64_MAX ;
 break ;
 }
 l = ( l * base ) + digit ;
 digit = * ++ p - '0' ;
 }
 return ( l ) ;
 }