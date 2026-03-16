static void U_CALLCONV _ISCIIOpen ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * errorCode ) {
 if ( pArgs -> onlyTestIsLoadable ) {
 return ;
 }
 cnv -> extraInfo = uprv_malloc ( sizeof ( UConverterDataISCII ) ) ;
 if ( cnv -> extraInfo != NULL ) {
 int32_t len = 0 ;
 UConverterDataISCII * converterData = ( UConverterDataISCII * ) cnv -> extraInfo ;
 converterData -> contextCharToUnicode = NO_CHAR_MARKER ;
 cnv -> toUnicodeStatus = missingCharMarker ;
 converterData -> contextCharFromUnicode = 0x0000 ;
 converterData -> resetToDefaultToUnicode = FALSE ;
 if ( ( pArgs -> options & UCNV_OPTIONS_VERSION_MASK ) < 9 ) {
 converterData -> currentDeltaFromUnicode = converterData -> currentDeltaToUnicode = converterData -> defDeltaToUnicode = ( uint16_t ) ( lookupInitialData [ pArgs -> options & UCNV_OPTIONS_VERSION_MASK ] . uniLang * DELTA ) ;
 converterData -> currentMaskFromUnicode = converterData -> currentMaskToUnicode = converterData -> defMaskToUnicode = lookupInitialData [ pArgs -> options & UCNV_OPTIONS_VERSION_MASK ] . maskEnum ;
 converterData -> isFirstBuffer = TRUE ;
 ( void ) uprv_strcpy ( converterData -> name , ISCII_CNV_PREFIX ) ;
 len = ( int32_t ) uprv_strlen ( converterData -> name ) ;
 converterData -> name [ len ] = ( char ) ( ( pArgs -> options & UCNV_OPTIONS_VERSION_MASK ) + '0' ) ;
 converterData -> name [ len + 1 ] = 0 ;
 converterData -> prevToUnicodeStatus = 0x0000 ;
 }
 else {
 uprv_free ( cnv -> extraInfo ) ;
 cnv -> extraInfo = NULL ;
 * errorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }
 else {
 * errorCode = U_MEMORY_ALLOCATION_ERROR ;
 }
 }