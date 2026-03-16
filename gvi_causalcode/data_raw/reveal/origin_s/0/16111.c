static void * U_CALLCONV myMemRealloc ( const void * context , void * mem , size_t size ) {
 char * p = ( char * ) mem ;
 char * retPtr ;
 if ( p != NULL ) {
 p -= sizeof ( ctest_AlignedMemory ) ;
 }
 retPtr = realloc ( p , size + sizeof ( ctest_AlignedMemory ) ) ;
 if ( retPtr != NULL ) {
 p += sizeof ( ctest_AlignedMemory ) ;
 }
 return retPtr ;
 }