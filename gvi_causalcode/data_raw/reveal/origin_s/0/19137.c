static guint strcase_hash ( gconstpointer key ) {
 const char * p = ( const char * ) key ;
 guint h = * p ;
 char c ;
 if ( h ) {
 if ( h >= 'A' && h <= 'Z' ) h = h - 'A' + 'a' ;
 for ( p += 1 ;
 * p != '\0' ;
 p ++ ) {
 c = * p ;
 if ( c >= 'A' && c <= 'Z' ) c = c - 'A' + 'a' ;
 h = ( h << 5 ) - h + c ;
 }
 }
 return h ;
 }