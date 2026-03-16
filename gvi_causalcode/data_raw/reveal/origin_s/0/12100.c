static int header_contains_non_alphanumdash ( ngx_str_t * key ) {
 unsigned int i ;
 for ( i = 0 ;
 i < key -> len ;
 i ++ ) {
 u_char c = key -> data [ i ] ;
 if ( ! ( c >= 'a' && c <= 'z' ) && ! ( c >= 'A' && c <= 'Z' ) && ! ( c == '-' ) && ! ( c >= '0' && c <= '9' ) ) {
 return 1 ;
 }
 }
 return 0 ;
 }