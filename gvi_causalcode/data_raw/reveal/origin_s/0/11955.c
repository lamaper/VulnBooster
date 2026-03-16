static UBool _isVariantSubtag ( const char * s , int32_t len ) {
 if ( len < 0 ) {
 len = ( int32_t ) uprv_strlen ( s ) ;
 }
 if ( len >= 5 && len <= 8 && _isAlphaNumericString ( s , len ) ) {
 return TRUE ;
 }
 if ( len == 4 && ISNUMERIC ( * s ) && _isAlphaNumericString ( s + 1 , 3 ) ) {
 return TRUE ;
 }
 return FALSE ;
 }