static void _appendLDMLExtensionAsKeywords ( const char * ldmlext , ExtensionListEntry * * appendTo , char * buf , int32_t bufSize , UBool * posixVariant , UErrorCode * status ) {
 const char * pTag ;
 const char * pKwds ;
 UBool variantExists = * posixVariant ;
 ExtensionListEntry * kwdFirst = NULL ;
 ExtensionListEntry * kwd , * nextKwd ;
 AttributeListEntry * attrFirst = NULL ;
 AttributeListEntry * attr , * nextAttr ;
 int32_t len ;
 int32_t bufIdx = 0 ;
 char attrBuf [ ULOC_KEYWORD_AND_VALUES_CAPACITY ] ;
 int32_t attrBufIdx = 0 ;
 * posixVariant = FALSE ;
 pTag = ldmlext ;
 pKwds = NULL ;
 while ( * pTag ) {
 for ( len = 0 ;
 * ( pTag + len ) && * ( pTag + len ) != SEP ;
 len ++ ) ;
 if ( ultag_isUnicodeLocaleKey ( pTag , len ) ) {
 pKwds = pTag ;
 break ;
 }
 attr = ( AttributeListEntry * ) uprv_malloc ( sizeof ( AttributeListEntry ) ) ;
 if ( attr == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 goto cleanup ;
 }
 if ( len < ( int32_t ) sizeof ( attrBuf ) - attrBufIdx ) {
 uprv_memcpy ( & attrBuf [ attrBufIdx ] , pTag , len ) ;
 attrBuf [ attrBufIdx + len ] = 0 ;
 attr -> attribute = & attrBuf [ attrBufIdx ] ;
 attrBufIdx += ( len + 1 ) ;
 }
 else {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 goto cleanup ;
 }
 if ( ! _addAttributeToList ( & attrFirst , attr ) ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 uprv_free ( attr ) ;
 goto cleanup ;
 }
 pTag += len ;
 if ( * pTag ) {
 pTag ++ ;
 }
 }
 if ( attrFirst ) {
 if ( attrBufIdx > bufSize ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 goto cleanup ;
 }
 kwd = ( ExtensionListEntry * ) uprv_malloc ( sizeof ( ExtensionListEntry ) ) ;
 if ( kwd == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 goto cleanup ;
 }
 kwd -> key = LOCALE_ATTRIBUTE_KEY ;
 kwd -> value = buf ;
 attr = attrFirst ;
 while ( attr != NULL ) {
 nextAttr = attr -> next ;
 if ( attr != attrFirst ) {
 * ( buf + bufIdx ) = SEP ;
 bufIdx ++ ;
 }
 len = uprv_strlen ( attr -> attribute ) ;
 uprv_memcpy ( buf + bufIdx , attr -> attribute , len ) ;
 bufIdx += len ;
 attr = nextAttr ;
 }
 * ( buf + bufIdx ) = 0 ;
 bufIdx ++ ;
 if ( ! _addExtensionToList ( & kwdFirst , kwd , FALSE ) ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 uprv_free ( kwd ) ;
 goto cleanup ;
 }
 attr = attrFirst ;
 while ( attr != NULL ) {
 nextAttr = attr -> next ;
 uprv_free ( attr ) ;
 attr = nextAttr ;
 }
 attrFirst = NULL ;
 }
 if ( pKwds ) {
 const char * pBcpKey = NULL ;
 const char * pBcpType = NULL ;
 int32_t bcpKeyLen = 0 ;
 int32_t bcpTypeLen = 0 ;
 UBool isDone = FALSE ;
 pTag = pKwds ;
 while ( ! isDone ) {
 const char * pNextBcpKey = NULL ;
 int32_t nextBcpKeyLen = 0 ;
 UBool emitKeyword = FALSE ;
 if ( * pTag ) {
 for ( len = 0 ;
 * ( pTag + len ) && * ( pTag + len ) != SEP ;
 len ++ ) ;
 if ( ultag_isUnicodeLocaleKey ( pTag , len ) ) {
 if ( pBcpKey ) {
 emitKeyword = TRUE ;
 pNextBcpKey = pTag ;
 nextBcpKeyLen = len ;
 }
 else {
 pBcpKey = pTag ;
 bcpKeyLen = len ;
 }
 }
 else {
 U_ASSERT ( pBcpKey != NULL ) ;
 if ( pBcpType ) {
 bcpTypeLen += ( len + 1 ) ;
 }
 else {
 pBcpType = pTag ;
 bcpTypeLen = len ;
 }
 }
 pTag += len ;
 if ( * pTag ) {
 pTag ++ ;
 }
 }
 else {
 emitKeyword = TRUE ;
 isDone = TRUE ;
 }
 if ( emitKeyword ) {
 const char * pKey = NULL ;
 const char * pType = NULL ;
 char bcpKeyBuf [ 9 ] ;
 U_ASSERT ( pBcpKey != NULL ) ;
 if ( bcpKeyLen >= sizeof ( bcpKeyBuf ) ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 goto cleanup ;
 }
 uprv_strncpy ( bcpKeyBuf , pBcpKey , bcpKeyLen ) ;
 bcpKeyBuf [ bcpKeyLen ] = 0 ;
 pKey = uloc_toLegacyKey ( bcpKeyBuf ) ;
 if ( pKey == NULL ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 goto cleanup ;
 }
 if ( pKey == bcpKeyBuf ) {
 T_CString_toLowerCase ( bcpKeyBuf ) ;
 if ( bufSize - bufIdx - 1 >= bcpKeyLen ) {
 uprv_memcpy ( buf + bufIdx , bcpKeyBuf , bcpKeyLen ) ;
 pKey = buf + bufIdx ;
 bufIdx += bcpKeyLen ;
 * ( buf + bufIdx ) = 0 ;
 bufIdx ++ ;
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 goto cleanup ;
 }
 }
 if ( pBcpType ) {
 char bcpTypeBuf [ 128 ] ;
 if ( bcpTypeLen >= sizeof ( bcpTypeBuf ) ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 goto cleanup ;
 }
 uprv_strncpy ( bcpTypeBuf , pBcpType , bcpTypeLen ) ;
 bcpTypeBuf [ bcpTypeLen ] = 0 ;
 pType = uloc_toLegacyType ( pKey , bcpTypeBuf ) ;
 if ( pType == NULL ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 goto cleanup ;
 }
 if ( pType == bcpTypeBuf ) {
 T_CString_toLowerCase ( bcpTypeBuf ) ;
 if ( bufSize - bufIdx - 1 >= bcpTypeLen ) {
 uprv_memcpy ( buf + bufIdx , bcpTypeBuf , bcpTypeLen ) ;
 pType = buf + bufIdx ;
 bufIdx += bcpTypeLen ;
 * ( buf + bufIdx ) = 0 ;
 bufIdx ++ ;
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 goto cleanup ;
 }
 }
 }
 else {
 pType = LOCALE_TYPE_YES ;
 }
 if ( ! variantExists && ! uprv_strcmp ( pKey , POSIX_KEY ) && ! uprv_strcmp ( pType , POSIX_VALUE ) ) {
 * posixVariant = TRUE ;
 }
 else {
 kwd = ( ExtensionListEntry * ) uprv_malloc ( sizeof ( ExtensionListEntry ) ) ;
 if ( kwd == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 goto cleanup ;
 }
 kwd -> key = pKey ;
 kwd -> value = pType ;
 if ( ! _addExtensionToList ( & kwdFirst , kwd , FALSE ) ) {
 * status = U_ILLEGAL_ARGUMENT_ERROR ;
 uprv_free ( kwd ) ;
 goto cleanup ;
 }
 }
 pBcpKey = pNextBcpKey ;
 bcpKeyLen = pNextBcpKey != NULL ? nextBcpKeyLen : 0 ;
 pBcpType = NULL ;
 bcpTypeLen = 0 ;
 }
 }
 }
 kwd = kwdFirst ;
 while ( kwd != NULL ) {
 nextKwd = kwd -> next ;
 _addExtensionToList ( appendTo , kwd , FALSE ) ;
 kwd = nextKwd ;
 }
 return ;
 cleanup : attr = attrFirst ;
 while ( attr != NULL ) {
 nextAttr = attr -> next ;
 uprv_free ( attr ) ;
 attr = nextAttr ;
 }
 kwd = kwdFirst ;
 while ( kwd != NULL ) {
 nextKwd = kwd -> next ;
 uprv_free ( kwd ) ;
 kwd = nextKwd ;
 }
 }