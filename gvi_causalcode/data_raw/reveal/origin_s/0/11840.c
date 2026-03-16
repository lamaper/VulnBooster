static int32_t U_CALLCONV uprv_copyArray32 ( const UDataSwapper * ds , const void * inData , int32_t length , void * outData , UErrorCode * pErrorCode ) {
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return 0 ;
 }
 if ( ds == NULL || inData == NULL || length < 0 || ( length & 3 ) != 0 || outData == NULL ) {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 if ( length > 0 && inData != outData ) {
 uprv_memcpy ( outData , inData , length ) ;
 }
 return length ;
 }