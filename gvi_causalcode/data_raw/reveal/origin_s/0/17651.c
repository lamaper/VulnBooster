char * utf8_verify_copy ( const char * str ) {
 if ( str == NULL ) return ( NULL ) ;
 if ( utf8_valid ( str ) ) return ( copy ( str ) ) ;
 return ( latin1_2_utf8_copy ( str ) ) ;
 }