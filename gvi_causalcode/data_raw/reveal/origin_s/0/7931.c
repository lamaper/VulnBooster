static uint16_t * encodeRunByte ( uint16_t * buffer , uint16_t * bufLimit , uint8_t value , int32_t length , uint8_t state [ ] , UErrorCode * status ) {
 if ( ! status || U_FAILURE ( * status ) ) {
 return NULL ;
 }
 if ( length < 4 ) {
 int32_t j = 0 ;
 for ( ;
 j < length ;
 ++ j ) {
 if ( value == ESCAPE_BYTE ) {
 buffer = appendEncodedByte ( buffer , bufLimit , ESCAPE_BYTE , state , status ) ;
 }
 buffer = appendEncodedByte ( buffer , bufLimit , value , state , status ) ;
 }
 }
 else {
 if ( length == ESCAPE_BYTE ) {
 if ( value == ESCAPE_BYTE ) {
 buffer = appendEncodedByte ( buffer , bufLimit , ESCAPE_BYTE , state , status ) ;
 }
 buffer = appendEncodedByte ( buffer , bufLimit , value , state , status ) ;
 -- length ;
 }
 buffer = appendEncodedByte ( buffer , bufLimit , ESCAPE_BYTE , state , status ) ;
 buffer = appendEncodedByte ( buffer , bufLimit , ( char ) length , state , status ) ;
 buffer = appendEncodedByte ( buffer , bufLimit , value , state , status ) ;
 }
 return buffer ;
 }