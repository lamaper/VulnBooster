static int evhttp_header_is_valid_value ( const char * value ) {
 const char * p = value ;
 while ( ( p = strpbrk ( p , "\r\n" ) ) != NULL ) {
 p += strspn ( p , "\r\n" ) ;
 if ( * p != ' ' && * p != '\t' ) return ( 0 ) ;
 }
 return ( 1 ) ;
 }