static void * U_CALLCONV myMemAlloc ( const void * context , size_t size ) {
 char * retPtr = ( char * ) malloc ( size + sizeof ( ctest_AlignedMemory ) ) ;
 if ( retPtr != NULL ) {
 retPtr += sizeof ( ctest_AlignedMemory ) ;
 }
 gBlockCount ++ ;
 return retPtr ;
 }