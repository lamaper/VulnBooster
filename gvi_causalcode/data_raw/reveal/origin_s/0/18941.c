static char * strsep ( char * * s , const char * del ) {
 char * d , * tok ;
 assert ( strlen ( del ) == 1 ) ;
 if ( ! s || ! * s ) return NULL ;
 tok = * s ;
 d = strstr ( tok , del ) ;
 if ( d ) {
 * d = '\0' ;
 * s = d + 1 ;
 }
 else * s = NULL ;
 return tok ;
 }