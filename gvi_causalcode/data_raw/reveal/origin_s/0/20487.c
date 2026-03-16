static int32_t U_CALLCONV uprv_swapArray32 ( const UDataSwapper * ds , const void * inData , int32_t length , void * outData , UErrorCode * pErrorCode ) {
 const uint32_t * p ;
 uint32_t * q ;
 int32_t count ;
 uint32_t x ;
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return 0 ;
 }
 if ( ds == NULL || inData == NULL || length < 0 || ( length & 3 ) != 0 || outData == NULL ) {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 p = ( const uint32_t * ) inData ;
 q = ( uint32_t * ) outData ;
 count = length / 4 ;
 while ( count > 0 ) {
 x = * p ++ ;
 * q ++ = ( uint32_t ) ( ( x << 24 ) | ( ( x << 8 ) & 0xff0000 ) | ( ( x >> 8 ) & 0xff00 ) | ( x >> 24 ) ) ;
 -- count ;
 }
 return length ;
 }