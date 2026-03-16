static UBool _isExtlangSubtag ( const char * s , int32_t len ) {
 if ( len < 0 ) {
 len = ( int32_t ) uprv_strlen ( s ) ;
 }
 if ( len == 3 && _isAlphaString ( s , len ) ) {
 return TRUE ;
 }
 return FALSE ;
 }