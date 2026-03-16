static int32_t setOneCode ( UScriptCode script , UScriptCode * scripts , int32_t capacity , UErrorCode * err ) {
 if ( U_FAILURE ( * err ) ) {
 return 0 ;
 }
 if ( 1 > capacity ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 return 1 ;
 }
 scripts [ 0 ] = script ;
 return 1 ;
 }