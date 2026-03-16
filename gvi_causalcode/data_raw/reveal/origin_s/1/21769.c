static void * size_checked_realloc ( void * ptr , size_t size ) {
 if ( size > MAX_LIBXML_MALLOC ) {
 * ( volatile char * ) 0 = '\0' ;
 return NULL ;
 }
 return realloc ( ptr , size ) ;
 }