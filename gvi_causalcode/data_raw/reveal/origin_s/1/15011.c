static int32_t _appendVariantsToLanguageTag ( const char * localeID , char * appendAt , int32_t capacity , UBool strict , UBool * hadPosix , UErrorCode * status ) {
 char buf [ ULOC_FULLNAME_CAPACITY ] ;
 UErrorCode tmpStatus = U_ZERO_ERROR ;
 int32_t len , i ;
 int32_t reslen = 0 ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 len = uloc_getVariant ( localeID , buf , sizeof ( buf ) , & tmpStatus ) ;
 if ( U_FAILURE ( tmpStatus ) || tmpStatus == U_STRING_NOT_TERMINATED_WARNING ) {
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 return 0 ;
 }
 if ( len > 0 ) {
 char * p , * pVar ;
 UBool bNext = TRUE ;
 VariantListEntry * var ;
 VariantListEntry * varFirst = NULL ;
 pVar = NULL ;
 p = buf ;
 while ( bNext ) {
 if ( * p == SEP || * p == LOCALE_SEP || * p == 0 ) {
 if ( * p == 0 ) {
 bNext = FALSE ;
 }
 else {
 * p = 0 ;
 }
 if ( pVar == NULL ) {
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 break ;
 }
 }
 else {
 for ( i = 0 ;
 * ( pVar + i ) != 0 ;
 i ++ ) {
 * ( pVar + i ) = uprv_tolower ( * ( pVar + i ) ) ;
 }
 if ( _isVariantSubtag ( pVar , - 1 ) ) {
 if ( uprv_strcmp ( pVar , POSIX_VALUE ) || len != uprv_strlen ( POSIX_VALUE ) ) {
 var = ( VariantListEntry * ) uprv_malloc ( sizeof ( VariantListEntry ) ) ;
 if ( var == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 break ;
 }
 var -> variant = pVar ;
 if ( ! _addVariantToList ( & varFirst , var ) ) {
 uprv_free ( var ) ;
 if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 break ;
 }
 }
 }
 else {
 * hadPosix = TRUE ;
 }
 }
 else if ( strict ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 break ;
 }
 else if ( _isPrivateuseValueSubtag ( pVar , - 1 ) ) {
 break ;
 }
 }
 pVar = NULL ;
 }
 else if ( pVar == NULL ) {
 pVar = p ;
 }
 p ++ ;
 }
 if ( U_SUCCESS ( * status ) ) {
 if ( varFirst != NULL ) {
 int32_t varLen ;
 var = varFirst ;
 while ( var != NULL ) {
 if ( reslen < capacity ) {
 * ( appendAt + reslen ) = SEP ;
 }
 reslen ++ ;
 varLen = ( int32_t ) uprv_strlen ( var -> variant ) ;
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , var -> variant , uprv_min ( varLen , capacity - reslen ) ) ;
 }
 reslen += varLen ;
 var = var -> next ;
 }
 }
 }
 var = varFirst ;
 while ( var != NULL ) {
 VariantListEntry * tmpVar = var -> next ;
 uprv_free ( var ) ;
 var = tmpVar ;
 }
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 }
 u_terminateChars ( appendAt , capacity , reslen , status ) ;
 return reslen ;
 }