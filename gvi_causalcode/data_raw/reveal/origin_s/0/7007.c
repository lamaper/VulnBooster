static int32_t _appendRegionToLanguageTag ( const char * localeID , char * appendAt , int32_t capacity , UBool strict , UErrorCode * status ) {
 char buf [ ULOC_COUNTRY_CAPACITY ] ;
 UErrorCode tmpStatus = U_ZERO_ERROR ;
 int32_t len ;
 int32_t reslen = 0 ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 len = uloc_getCountry ( localeID , buf , sizeof ( buf ) , & tmpStatus ) ;
 if ( U_FAILURE ( tmpStatus ) || tmpStatus == U_STRING_NOT_TERMINATED_WARNING ) {
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 return 0 ;
 }
 if ( len > 0 ) {
 if ( ! _isRegionSubtag ( buf , len ) ) {
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 return 0 ;
 }
 else {
 if ( reslen < capacity ) {
 * ( appendAt + reslen ) = SEP ;
 }
 reslen ++ ;
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , buf , uprv_min ( len , capacity - reslen ) ) ;
 }
 reslen += len ;
 }
 }
 u_terminateChars ( appendAt , capacity , reslen , status ) ;
 return reslen ;
 }