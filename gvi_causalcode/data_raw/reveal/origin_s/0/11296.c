int32_t byteArrayToRLEString ( const uint8_t * src , int32_t srcLen , uint16_t * buffer , int32_t bufLen , UErrorCode * status ) {
 const uint16_t * saveBuf = buffer ;
 uint16_t * bufLimit = buffer + bufLen ;
 if ( buffer < bufLimit ) {
 * buffer ++ = ( ( uint16_t ) ( srcLen >> 16 ) ) ;
 if ( buffer < bufLimit ) {
 uint8_t runValue = src [ 0 ] ;
 int runLength = 1 ;
 uint8_t state [ 2 ] = {
 0 }
 ;
 int i = 1 ;
 * buffer ++ = ( ( uint16_t ) srcLen ) ;
 for ( ;
 i < srcLen ;
 ++ i ) {
 uint8_t b = src [ i ] ;
 if ( b == runValue && runLength < 0xFF ) {
 ++ runLength ;
 }
 else {
 buffer = encodeRunByte ( buffer , bufLimit , runValue , runLength , state , status ) ;
 runValue = b ;
 runLength = 1 ;
 }
 }
 buffer = encodeRunByte ( buffer , bufLimit , runValue , runLength , state , status ) ;
 if ( state [ 0 ] != 0 ) {
 buffer = appendEncodedByte ( buffer , bufLimit , 0 , state , status ) ;
 }
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 }
 return ( int32_t ) ( buffer - saveBuf ) ;
 }