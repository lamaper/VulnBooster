static UBool _isExtensionSubtag ( const char * s , int32_t len ) {
 if ( len < 0 ) {
 len = ( int32_t ) uprv_strlen ( s ) ;
 }
 if ( len >= 2 && len <= 8 && _isAlphaNumericString ( s , len ) ) {
 return TRUE ;
 }
 return FALSE ;
 }