static int32_t U_CALLCONV uprv_swapArray64 ( const UDataSwapper * ds , const void * inData , int32_t length , void * outData , UErrorCode * pErrorCode ) {
 const uint64_t * p ;
 uint64_t * q ;
 int32_t count ;
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return 0 ;
 }
 if ( ds == NULL || inData == NULL || length < 0 || ( length & 7 ) != 0 || outData == NULL ) {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 p = ( const uint64_t * ) inData ;
 q = ( uint64_t * ) outData ;
 count = length / 8 ;
 while ( count > 0 ) {
 uint64_t x = * p ++ ;
 x = ( x << 56 ) | ( ( x & 0xff00 ) << 40 ) | ( ( x & 0xff0000 ) << 24 ) | ( ( x & 0xff000000 ) << 8 ) | ( ( x >> 8 ) & 0xff000000 ) | ( ( x >> 24 ) & 0xff0000 ) | ( ( x >> 40 ) & 0xff00 ) | ( x >> 56 ) ;
 * q ++ = x ;
 -- count ;
 }
 return length ;
 }