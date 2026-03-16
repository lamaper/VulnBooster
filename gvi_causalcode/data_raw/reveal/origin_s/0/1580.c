int32_t usArrayToRLEString ( const uint16_t * src , int32_t srcLen , uint16_t * buffer , int32_t bufLen , UErrorCode * status ) {
 uint16_t * bufLimit = buffer + bufLen ;
 uint16_t * saveBuffer = buffer ;
 if ( buffer < bufLimit ) {
 * buffer ++ = ( uint16_t ) ( srcLen >> 16 ) ;
 if ( buffer < bufLimit ) {
 uint16_t runValue = src [ 0 ] ;
 int32_t runLength = 1 ;
 int i = 1 ;
 * buffer ++ = ( uint16_t ) srcLen ;
 for ( ;
 i < srcLen ;
 ++ i ) {
 uint16_t s = src [ i ] ;
 if ( s == runValue && runLength < 0xFFFF ) {
 ++ runLength ;
 }
 else {
 buffer = encodeRunShort ( buffer , bufLimit , ( uint16_t ) runValue , runLength , status ) ;
 runValue = s ;
 runLength = 1 ;
 }
 }
 buffer = encodeRunShort ( buffer , bufLimit , ( uint16_t ) runValue , runLength , status ) ;
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 }
 return ( int32_t ) ( buffer - saveBuffer ) ;
 }