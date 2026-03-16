static void _UTF16Open ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * pErrorCode ) {
 if ( UCNV_GET_VERSION ( cnv ) <= 2 ) {
 if ( UCNV_GET_VERSION ( cnv ) == 2 && ! pArgs -> onlyTestIsLoadable ) {
 cnv -> sharedData = ( UConverterSharedData * ) & _UTF16v2Data ;
 uprv_memcpy ( cnv -> subChars , _UTF16v2Data . staticData -> subChar , UCNV_MAX_SUBCHAR_LEN ) ;
 }
 _UTF16Reset ( cnv , UCNV_RESET_BOTH ) ;
 }
 else {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }