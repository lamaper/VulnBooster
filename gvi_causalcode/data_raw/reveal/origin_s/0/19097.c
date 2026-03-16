static uint16_t * encodeRunShort ( uint16_t * buffer , uint16_t * bufLimit , uint16_t value , int32_t length , UErrorCode * status ) {
 int32_t num = 0 ;
 if ( length < 4 ) {
 int j = 0 ;
 for ( ;
 j < length ;
 ++ j ) {
 if ( value == ( int32_t ) ESCAPE ) {
 APPEND ( buffer , bufLimit , ESCAPE , num , status ) ;
 }
 APPEND ( buffer , bufLimit , value , num , status ) ;
 }
 }
 else {
 if ( length == ( int32_t ) ESCAPE ) {
 if ( value == ( int32_t ) ESCAPE ) {
 APPEND ( buffer , bufLimit , ESCAPE , num , status ) ;
 }
 APPEND ( buffer , bufLimit , value , num , status ) ;
 -- length ;
 }
 APPEND ( buffer , bufLimit , ESCAPE , num , status ) ;
 APPEND ( buffer , bufLimit , ( uint16_t ) length , num , status ) ;
 APPEND ( buffer , bufLimit , ( uint16_t ) value , num , status ) ;
 }
 return buffer ;
 }