static void U_CALLCONV myMemFree ( const void * context , void * mem ) {
 char * freePtr = ( char * ) mem ;
 if ( freePtr != NULL ) {
 freePtr -= sizeof ( ctest_AlignedMemory ) ;
 }
 free ( freePtr ) ;
 }