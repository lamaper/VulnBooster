static UBool _isNumericString ( const char * s , int32_t len ) {
 int32_t i ;
 for ( i = 0 ;
 i < len ;
 i ++ ) {
 if ( ! ISNUMERIC ( * ( s + i ) ) ) {
 return FALSE ;
 }
 }
 return TRUE ;
 }