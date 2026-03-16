static void DefaultFreeFunc ( void * opaque , void * address ) {
 BROTLI_UNUSED ( opaque ) ;
 free ( address ) ;
 }