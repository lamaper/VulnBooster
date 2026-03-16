static ULanguageTag * ultag_parse ( const char * tag , int32_t tagLen , int32_t * parsedLen , UErrorCode * status ) {
 ULanguageTag * t ;
 char * tagBuf ;
 int16_t next ;
 char * pSubtag , * pNext , * pLastGoodPosition ;
 int32_t subtagLen ;
 int32_t extlangIdx ;
 ExtensionListEntry * pExtension ;
 char * pExtValueSubtag , * pExtValueSubtagEnd ;
 int32_t i ;
 UBool privateuseVar = FALSE ;
 int32_t grandfatheredLen = 0 ;
 if ( parsedLen != NULL ) {
 * parsedLen = 0 ;
 }
 if ( U_FAILURE ( * status ) ) {
 return NULL ;
 }
 if ( tagLen < 0 ) {
 tagLen = ( int32_t ) uprv_strlen ( tag ) ;
 }
 tagBuf = ( char * ) uprv_malloc ( tagLen + 1 ) ;
 if ( tagBuf == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 return NULL ;
 }
 uprv_memcpy ( tagBuf , tag , tagLen ) ;
 * ( tagBuf + tagLen ) = 0 ;
 t = ( ULanguageTag * ) uprv_malloc ( sizeof ( ULanguageTag ) ) ;
 if ( t == NULL ) {
 uprv_free ( tagBuf ) ;
 * status = U_MEMORY_ALLOCATION_ERROR ;
 return NULL ;
 }
 _initializeULanguageTag ( t ) ;
 t -> buf = tagBuf ;
 if ( tagLen < MINLEN ) {
 return t ;
 }
 for ( i = 0 ;
 GRANDFATHERED [ i ] != NULL ;
 i += 2 ) {
 if ( uprv_stricmp ( GRANDFATHERED [ i ] , tagBuf ) == 0 ) {
 int32_t newTagLength ;
 grandfatheredLen = tagLen ;
 newTagLength = uprv_strlen ( GRANDFATHERED [ i + 1 ] ) ;
 if ( tagLen < newTagLength ) {
 uprv_free ( tagBuf ) ;
 tagBuf = ( char * ) uprv_malloc ( newTagLength + 1 ) ;
 if ( tagBuf == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 ultag_close ( t ) ;
 return NULL ;
 }
 t -> buf = tagBuf ;
 tagLen = newTagLength ;
 }
 uprv_strcpy ( t -> buf , GRANDFATHERED [ i + 1 ] ) ;
 break ;
 }
 }
 next = LANG | PRIV ;
 pNext = pLastGoodPosition = tagBuf ;
 extlangIdx = 0 ;
 pExtension = NULL ;
 pExtValueSubtag = NULL ;
 pExtValueSubtagEnd = NULL ;
 while ( pNext ) {
 char * pSep ;
 pSubtag = pNext ;
 pSep = pSubtag ;
 while ( * pSep ) {
 if ( * pSep == SEP ) {
 break ;
 }
 pSep ++ ;
 }
 if ( * pSep == 0 ) {
 pNext = NULL ;
 }
 else {
 pNext = pSep + 1 ;
 }
 subtagLen = ( int32_t ) ( pSep - pSubtag ) ;
 if ( next & LANG ) {
 if ( _isLanguageSubtag ( pSubtag , subtagLen ) ) {
 * pSep = 0 ;
 t -> language = T_CString_toLowerCase ( pSubtag ) ;
 pLastGoodPosition = pSep ;
 next = EXTL | SCRT | REGN | VART | EXTS | PRIV ;
 continue ;
 }
 }
 if ( next & EXTL ) {
 if ( _isExtlangSubtag ( pSubtag , subtagLen ) ) {
 * pSep = 0 ;
 t -> extlang [ extlangIdx ++ ] = T_CString_toLowerCase ( pSubtag ) ;
 pLastGoodPosition = pSep ;
 if ( extlangIdx < 3 ) {
 next = EXTL | SCRT | REGN | VART | EXTS | PRIV ;
 }
 else {
 next = SCRT | REGN | VART | EXTS | PRIV ;
 }
 continue ;
 }
 }
 if ( next & SCRT ) {
 if ( _isScriptSubtag ( pSubtag , subtagLen ) ) {
 char * p = pSubtag ;
 * pSep = 0 ;
 * p = uprv_toupper ( * p ) ;
 p ++ ;
 for ( ;
 * p ;
 p ++ ) {
 * p = uprv_tolower ( * p ) ;
 }
 t -> script = pSubtag ;
 pLastGoodPosition = pSep ;
 next = REGN | VART | EXTS | PRIV ;
 continue ;
 }
 }
 if ( next & REGN ) {
 if ( _isRegionSubtag ( pSubtag , subtagLen ) ) {
 * pSep = 0 ;
 t -> region = T_CString_toUpperCase ( pSubtag ) ;
 pLastGoodPosition = pSep ;
 next = VART | EXTS | PRIV ;
 continue ;
 }
 }
 if ( next & VART ) {
 if ( _isVariantSubtag ( pSubtag , subtagLen ) || ( privateuseVar && _isPrivateuseVariantSubtag ( pSubtag , subtagLen ) ) ) {
 VariantListEntry * var ;
 UBool isAdded ;
 var = ( VariantListEntry * ) uprv_malloc ( sizeof ( VariantListEntry ) ) ;
 if ( var == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 goto error ;
 }
 * pSep = 0 ;
 var -> variant = T_CString_toUpperCase ( pSubtag ) ;
 isAdded = _addVariantToList ( & ( t -> variants ) , var ) ;
 if ( ! isAdded ) {
 uprv_free ( var ) ;
 break ;
 }
 pLastGoodPosition = pSep ;
 next = VART | EXTS | PRIV ;
 continue ;
 }
 }
 if ( next & EXTS ) {
 if ( _isExtensionSingleton ( pSubtag , subtagLen ) ) {
 if ( pExtension != NULL ) {
 if ( pExtValueSubtag == NULL || pExtValueSubtagEnd == NULL ) {
 uprv_free ( pExtension ) ;
 pExtension = NULL ;
 break ;
 }
 * pExtValueSubtagEnd = 0 ;
 pExtension -> value = T_CString_toLowerCase ( pExtValueSubtag ) ;
 if ( _addExtensionToList ( & ( t -> extensions ) , pExtension , FALSE ) ) {
 pLastGoodPosition = pExtValueSubtagEnd ;
 }
 else {
 uprv_free ( pExtension ) ;
 pExtension = NULL ;
 break ;
 }
 }
 pExtension = ( ExtensionListEntry * ) uprv_malloc ( sizeof ( ExtensionListEntry ) ) ;
 if ( pExtension == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 goto error ;
 }
 * pSep = 0 ;
 pExtension -> key = T_CString_toLowerCase ( pSubtag ) ;
 pExtension -> value = NULL ;
 pExtValueSubtag = NULL ;
 pExtValueSubtagEnd = NULL ;
 next = EXTV ;
 continue ;
 }
 }
 if ( next & EXTV ) {
 if ( _isExtensionSubtag ( pSubtag , subtagLen ) ) {
 if ( pExtValueSubtag == NULL ) {
 pExtValueSubtag = pSubtag ;
 }
 pExtValueSubtagEnd = pSep ;
 next = EXTS | EXTV | PRIV ;
 continue ;
 }
 }
 if ( next & PRIV ) {
 if ( uprv_tolower ( * pSubtag ) == PRIVATEUSE ) {
 char * pPrivuseVal ;
 if ( pExtension != NULL ) {
 if ( pExtValueSubtag == NULL || pExtValueSubtagEnd == NULL ) {
 uprv_free ( pExtension ) ;
 pExtension = NULL ;
 break ;
 }
 else {
 * pExtValueSubtagEnd = 0 ;
 pExtension -> value = T_CString_toLowerCase ( pExtValueSubtag ) ;
 if ( _addExtensionToList ( & ( t -> extensions ) , pExtension , FALSE ) ) {
 pLastGoodPosition = pExtValueSubtagEnd ;
 pExtension = NULL ;
 }
 else {
 uprv_free ( pExtension ) ;
 pExtension = NULL ;
 break ;
 }
 }
 }
 if ( pNext == NULL ) {
 break ;
 }
 pPrivuseVal = pNext ;
 while ( pNext ) {
 pSubtag = pNext ;
 pSep = pSubtag ;
 while ( * pSep ) {
 if ( * pSep == SEP ) {
 break ;
 }
 pSep ++ ;
 }
 if ( * pSep == 0 ) {
 pNext = NULL ;
 }
 else {
 pNext = pSep + 1 ;
 }
 subtagLen = ( int32_t ) ( pSep - pSubtag ) ;
 if ( uprv_strncmp ( pSubtag , PRIVUSE_VARIANT_PREFIX , uprv_strlen ( PRIVUSE_VARIANT_PREFIX ) ) == 0 ) {
 * pSep = 0 ;
 next = VART ;
 privateuseVar = TRUE ;
 break ;
 }
 else if ( _isPrivateuseValueSubtag ( pSubtag , subtagLen ) ) {
 pLastGoodPosition = pSep ;
 }
 else {
 break ;
 }
 }
 if ( next == VART ) {
 continue ;
 }
 if ( pLastGoodPosition - pPrivuseVal > 0 ) {
 * pLastGoodPosition = 0 ;
 t -> privateuse = T_CString_toLowerCase ( pPrivuseVal ) ;
 }
 break ;
 }
 break ;
 }
 break ;
 }
 if ( pExtension != NULL ) {
 if ( pExtValueSubtag == NULL || pExtValueSubtagEnd == NULL ) {
 uprv_free ( pExtension ) ;
 }
 else {
 * pExtValueSubtagEnd = 0 ;
 pExtension -> value = T_CString_toLowerCase ( pExtValueSubtag ) ;
 if ( _addExtensionToList ( & ( t -> extensions ) , pExtension , FALSE ) ) {
 pLastGoodPosition = pExtValueSubtagEnd ;
 }
 else {
 uprv_free ( pExtension ) ;
 }
 }
 }
 if ( parsedLen != NULL ) {
 * parsedLen = ( grandfatheredLen > 0 ) ? grandfatheredLen : ( int32_t ) ( pLastGoodPosition - t -> buf ) ;
 }
 return t ;
 error : ultag_close ( t ) ;
 return NULL ;
 }