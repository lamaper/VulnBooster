static int32_t U_CALLCONV uprv_swapArray16 ( const UDataSwapper * ds , const void * inData , int32_t length , void * outData , UErrorCode * pErrorCode ) {
 const uint16_t * p ;
 uint16_t * q ;
 int32_t count ;
 uint16_t x ;
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return 0 ;
 }
 if ( ds == NULL || inData == NULL || length < 0 || ( length & 1 ) != 0 || outData == NULL ) {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 p = ( const uint16_t * ) inData ;
 q = ( uint16_t * ) outData ;
 count = length / 2 ;
 while ( count > 0 ) {
 x = * p ++ ;
 * q ++ = ( uint16_t ) ( ( x << 8 ) | ( x >> 8 ) ) ;
 -- count ;
 }
 return length ;
 }