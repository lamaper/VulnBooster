static char * allocString ( uint32_t length ) {
 uint32_t top = stringTop + length ;
 char * p ;
 if ( top > STRING_STORE_SIZE ) {
 fprintf ( stderr , "gencmn: out of memory\n" ) ;
 exit ( U_MEMORY_ALLOCATION_ERROR ) ;
 }
 p = stringStore + stringTop ;
 stringTop = top ;
 return p ;
 }