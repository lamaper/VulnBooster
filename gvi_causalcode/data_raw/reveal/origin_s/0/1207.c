static void quickSort ( char * array , int32_t length , int32_t itemSize , UComparator * cmp , const void * context , UErrorCode * pErrorCode ) {
 UAlignedMemory xw [ ( 2 * STACK_ITEM_SIZE ) / sizeof ( UAlignedMemory ) + 1 ] ;
 void * p ;
 if ( itemSize <= STACK_ITEM_SIZE ) {
 p = xw ;
 }
 else {
 p = uprv_malloc ( 2 * itemSize ) ;
 if ( p == NULL ) {
 * pErrorCode = U_MEMORY_ALLOCATION_ERROR ;
 return ;
 }
 }
 subQuickSort ( array , 0 , length , itemSize , cmp , context , p , ( char * ) p + itemSize ) ;
 if ( p != xw ) {
 uprv_free ( p ) ;
 }
 }