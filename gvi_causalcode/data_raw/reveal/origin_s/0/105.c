static UBool _isRegionSubtag ( const char * s , int32_t len ) {
 if ( len < 0 ) {
 len = ( int32_t ) uprv_strlen ( s ) ;
 }
 if ( len == 2 && _isAlphaString ( s , len ) ) {
 return TRUE ;
 }
 if ( len == 3 && _isNumericString ( s , len ) ) {
 return TRUE ;
 }
 return FALSE ;
 }