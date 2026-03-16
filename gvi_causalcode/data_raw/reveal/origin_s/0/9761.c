static uint16_t * appendEncodedByte ( uint16_t * buffer , uint16_t * buffLimit , uint8_t value , uint8_t state [ ] , UErrorCode * status ) {
 if ( ! status || U_FAILURE ( * status ) ) {
 return NULL ;
 }
 if ( state [ 0 ] != 0 ) {
 uint16_t c = ( uint16_t ) ( ( state [ 1 ] << 8 ) | ( ( ( int32_t ) value ) & 0xFF ) ) ;
 if ( buffer < buffLimit ) {
 * buffer ++ = c ;
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 }
 state [ 0 ] = 0 ;
 return buffer ;
 }
 else {
 state [ 0 ] = 1 ;
 state [ 1 ] = value ;
 return buffer ;
 }
 }