static void UnblendFree ( StemInfo * h ) {
 while ( h != NULL ) {
 chunkfree ( h -> u . unblended , sizeof ( real [ 2 ] [ MmMax ] ) ) ;
 h -> u . unblended = NULL ;
 h = h -> next ;
 }
 }