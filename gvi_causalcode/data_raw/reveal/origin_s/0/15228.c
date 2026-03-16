static bool peek_ipv6 ( const char * str , size_t * skip ) {
 size_t i = 0 ;
 size_t colons = 0 ;
 if ( str [ i ++ ] != '[' ) {
 return FALSE ;
 }
 for ( ;
 ;
 ) {
 const char c = str [ i ++ ] ;
 if ( ISALNUM ( c ) || c == '.' || c == '%' ) {
 }
 else if ( c == ':' ) {
 colons ++ ;
 }
 else if ( c == ']' ) {
 * skip = i ;
 return colons >= 2 ? TRUE : FALSE ;
 }
 else {
 return FALSE ;
 }
 }
 }