static int32_t setCodes ( const UScriptCode * src , int32_t length , UScriptCode * dest , int32_t capacity , UErrorCode * err ) {
 int32_t i ;
 if ( U_FAILURE ( * err ) ) {
 return 0 ;
 }
 if ( length > capacity ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 return length ;
 }
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 dest [ i ] = src [ i ] ;
 }
 return length ;
 }