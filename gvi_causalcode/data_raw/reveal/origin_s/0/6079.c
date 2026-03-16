static UBool _isExtensionSingleton ( const char * s , int32_t len ) {
 if ( len < 0 ) {
 len = ( int32_t ) uprv_strlen ( s ) ;
 }
 if ( len == 1 && ISALPHA ( * s ) && ( uprv_tolower ( * s ) != PRIVATEUSE ) ) {
 return TRUE ;
 }
 return FALSE ;
 }