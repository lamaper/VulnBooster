static void updateSrc ( UBiDiTransform * pTransform , const UChar * newSrc , uint32_t newLength , uint32_t newSize , UErrorCode * pErrorCode ) {
 if ( newSize < newLength ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return ;
 }
 if ( newSize > pTransform -> srcSize ) {
 newSize += 50 ;
 if ( pTransform -> src != NULL ) {
 uprv_free ( pTransform -> src ) ;
 pTransform -> src = NULL ;
 }
 pTransform -> src = ( UChar * ) uprv_malloc ( newSize * sizeof ( UChar ) ) ;
 if ( pTransform -> src == NULL ) {
 * pErrorCode = U_MEMORY_ALLOCATION_ERROR ;
 return ;
 }
 pTransform -> srcSize = newSize ;
 }
 u_strncpy ( pTransform -> src , newSrc , newLength ) ;
 pTransform -> srcLength = u_terminateUChars ( pTransform -> src , pTransform -> srcSize , newLength , pErrorCode ) ;
 }