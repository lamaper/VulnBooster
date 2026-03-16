static void rfc2231_escape ( string_t * dest , const char * src ) {
 for ( ;
 * src != '\0' ;
 src ++ ) {
 if ( * src == '%' ) str_append ( dest , "%25" ) ;
 else str_append_c ( dest , * src ) ;
 }
 }