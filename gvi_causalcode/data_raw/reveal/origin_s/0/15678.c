static int32_t _appendKeywords ( ULanguageTag * langtag , char * appendAt , int32_t capacity , UErrorCode * status ) {
 int32_t reslen = 0 ;
 int32_t i , n ;
 int32_t len ;
 ExtensionListEntry * kwdFirst = NULL ;
 ExtensionListEntry * kwd ;
 const char * key , * type ;
 char * kwdBuf = NULL ;
 int32_t kwdBufLength = capacity ;
 UBool posixVariant = FALSE ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 kwdBuf = ( char * ) uprv_malloc ( kwdBufLength ) ;
 if ( kwdBuf == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 return 0 ;
 }
 if ( ultag_getVariantsSize ( langtag ) ) {
 posixVariant = TRUE ;
 }
 n = ultag_getExtensionsSize ( langtag ) ;
 for ( i = 0 ;
 i < n ;
 i ++ ) {
 key = ultag_getExtensionKey ( langtag , i ) ;
 type = ultag_getExtensionValue ( langtag , i ) ;
 if ( * key == LDMLEXT ) {
 _appendLDMLExtensionAsKeywords ( type , & kwdFirst , kwdBuf , kwdBufLength , & posixVariant , status ) ;
 if ( U_FAILURE ( * status ) ) {
 break ;
 }
 }
 else {
 kwd = ( ExtensionListEntry * ) uprv_malloc ( sizeof ( ExtensionListEntry ) ) ;
 if ( kwd == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 break ;
 }
 kwd -> key = key ;
 kwd -> value = type ;
 if ( ! _addExtensionToList ( & kwdFirst , kwd , FALSE ) ) {
 uprv_free ( kwd ) ;
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 break ;
 }
 }
 }
 if ( U_SUCCESS ( * status ) ) {
 type = ultag_getPrivateUse ( langtag ) ;
 if ( ( int32_t ) uprv_strlen ( type ) > 0 ) {
 kwd = ( ExtensionListEntry * ) uprv_malloc ( sizeof ( ExtensionListEntry ) ) ;
 if ( kwd == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 }
 else {
 kwd -> key = PRIVATEUSE_KEY ;
 kwd -> value = type ;
 if ( ! _addExtensionToList ( & kwdFirst , kwd , FALSE ) ) {
 uprv_free ( kwd ) ;
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }
 }
 }
 if ( U_SUCCESS ( * status ) && posixVariant ) {
 len = ( int32_t ) uprv_strlen ( _POSIX ) ;
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , _POSIX , uprv_min ( len , capacity - reslen ) ) ;
 }
 reslen += len ;
 }
 if ( U_SUCCESS ( * status ) && kwdFirst != NULL ) {
 UBool firstValue = TRUE ;
 kwd = kwdFirst ;
 do {
 if ( reslen < capacity ) {
 if ( firstValue ) {
 * ( appendAt + reslen ) = LOCALE_EXT_SEP ;
 firstValue = FALSE ;
 }
 else {
 * ( appendAt + reslen ) = LOCALE_KEYWORD_SEP ;
 }
 }
 reslen ++ ;
 len = ( int32_t ) uprv_strlen ( kwd -> key ) ;
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , kwd -> key , uprv_min ( len , capacity - reslen ) ) ;
 }
 reslen += len ;
 if ( reslen < capacity ) {
 * ( appendAt + reslen ) = LOCALE_KEY_TYPE_SEP ;
 }
 reslen ++ ;
 len = ( int32_t ) uprv_strlen ( kwd -> value ) ;
 if ( reslen < capacity ) {
 uprv_memcpy ( appendAt + reslen , kwd -> value , uprv_min ( len , capacity - reslen ) ) ;
 }
 reslen += len ;
 kwd = kwd -> next ;
 }
 while ( kwd ) ;
 }
 kwd = kwdFirst ;
 while ( kwd != NULL ) {
 ExtensionListEntry * tmpKwd = kwd -> next ;
 uprv_free ( kwd ) ;
 kwd = tmpKwd ;
 }
 uprv_free ( kwdBuf ) ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 return u_terminateChars ( appendAt , capacity , reslen , status ) ;
 }