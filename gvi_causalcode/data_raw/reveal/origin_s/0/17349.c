static void insertionSort ( char * array , int32_t length , int32_t itemSize , UComparator * cmp , const void * context , UErrorCode * pErrorCode ) {
 UAlignedMemory v [ STACK_ITEM_SIZE / sizeof ( UAlignedMemory ) + 1 ] ;
 void * pv ;
 if ( itemSize <= STACK_ITEM_SIZE ) {
 pv = v ;
 }
 else {
 pv = uprv_malloc ( itemSize ) ;
 if ( pv == NULL ) {
 * pErrorCode = U_MEMORY_ALLOCATION_ERROR ;
 return ;
 }
 }
 doInsertionSort ( array , length , itemSize , cmp , context , pv ) ;
 if ( pv != v ) {
 uprv_free ( pv ) ;
 }
 }