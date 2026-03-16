static int32_t _appendLanguageToLanguageTag ( const char * localeID , char * appendAt , int32_t capacity , UBool strict , UErrorCode * status ) {
 char buf [ ULOC_LANG_CAPACITY ] ;
 UErrorCode tmpStatus = U_ZERO_ERROR ;
 int32_t len , i ;
 int32_t reslen = 0 ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 len = uloc_getLanguage ( localeID , buf , sizeof ( buf ) , & tmpStatus ) ;
 if ( U_FAILURE ( tmpStatus ) || tmpStatus == U_STRING_NOT_TERMINATED_WARNING ) {
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 len = 0 ;
 }
 if ( len == 0 ) {
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , LANG_UND , uprv_min ( LANG_UND_LEN , capacity - reslen ) ) ;
 }
 reslen += LANG_UND_LEN ;
 }
 else if ( ! _isLanguageSubtag ( buf , len ) ) {
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , LANG_UND , uprv_min ( LANG_UND_LEN , capacity - reslen ) ) ;
 }
 reslen += LANG_UND_LEN ;
 }
 else {
 for ( i = 0 ;
 i < UPRV_LENGTHOF ( DEPRECATEDLANGS ) ;
 i += 2 ) {
 if ( uprv_compareInvCharsAsAscii ( buf , DEPRECATEDLANGS [ i ] ) == 0 ) {
 uprv_strcpy ( buf , DEPRECATEDLANGS [ i + 1 ] ) ;
 len = ( int32_t ) uprv_strlen ( buf ) ;
 break ;
 }
 }
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , buf , uprv_min ( len , capacity - reslen ) ) ;
 }
 reslen += len ;
 }
 u_terminateChars ( appendAt , capacity , reslen , status ) ;
 return reslen ;
 }