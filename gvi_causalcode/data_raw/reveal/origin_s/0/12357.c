static void doInsertionSort ( char * array , int32_t length , int32_t itemSize , UComparator * cmp , const void * context , void * pv ) {
 int32_t j ;
 for ( j = 1 ;
 j < length ;
 ++ j ) {
 char * item = array + j * itemSize ;
 int32_t insertionPoint = uprv_stableBinarySearch ( array , j , item , itemSize , cmp , context ) ;
 if ( insertionPoint < 0 ) {
 insertionPoint = ~ insertionPoint ;
 }
 else {
 ++ insertionPoint ;
 }
 if ( insertionPoint < j ) {
 char * dest = array + insertionPoint * itemSize ;
 uprv_memcpy ( pv , item , itemSize ) ;
 uprv_memmove ( dest + itemSize , dest , ( j - insertionPoint ) * ( size_t ) itemSize ) ;
 uprv_memcpy ( dest , pv , itemSize ) ;
 }
 }
 }