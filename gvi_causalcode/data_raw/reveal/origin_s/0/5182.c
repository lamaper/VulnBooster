CharList * pkg_appendToList ( CharList * l , CharList * * end , const char * str ) {
 CharList * endptr = NULL , * tmp ;
 if ( end == NULL ) {
 end = & endptr ;
 }
 if ( ( * end == NULL ) && ( l != NULL ) ) {
 tmp = l ;
 while ( tmp -> next ) {
 tmp = tmp -> next ;
 }
 * end = tmp ;
 }
 if ( l == NULL ) {
 l = pkg_prependToList ( NULL , str ) ;
 }
 else {
 ( * end ) -> next = pkg_prependToList ( NULL , str ) ;
 }
 if ( * end ) {
 ( * end ) = ( * end ) -> next ;
 }
 else {
 * end = l ;
 }
 return l ;
 }