static int evhttp_decode_uri_internal ( const char * uri , size_t length , char * ret , int always_decode_plus ) {
 char c ;
 int i , j , in_query = always_decode_plus ;
 for ( i = j = 0 ;
 uri [ i ] != '\0' ;
 i ++ ) {
 c = uri [ i ] ;
 if ( c == '?' ) {
 in_query = 1 ;
 }
 else if ( c == '+' && in_query ) {
 c = ' ' ;
 }
 else if ( c == '%' && isxdigit ( ( unsigned char ) uri [ i + 1 ] ) && isxdigit ( ( unsigned char ) uri [ i + 2 ] ) ) {
 char tmp [ ] = {
 uri [ i + 1 ] , uri [ i + 2 ] , '\0' }
 ;
 c = ( char ) strtol ( tmp , NULL , 16 ) ;
 i += 2 ;
 }
 ret [ j ++ ] = c ;
 }
 ret [ j ] = '\0' ;
 return ( j ) ;
 }