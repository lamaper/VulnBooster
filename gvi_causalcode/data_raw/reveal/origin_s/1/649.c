static void _SCSUOpen ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * pErrorCode ) {
 const char * locale = pArgs -> locale ;
 if ( pArgs -> onlyTestIsLoadable ) {
 return ;
 }
 cnv -> extraInfo = uprv_malloc ( sizeof ( SCSUData ) ) ;
 if ( cnv -> extraInfo != NULL ) {
 if ( locale != NULL && locale [ 0 ] == 'j' && locale [ 1 ] == 'a' && ( locale [ 2 ] == 0 || locale [ 2 ] == '_' ) ) {
 ( ( SCSUData * ) cnv -> extraInfo ) -> locale = l_ja ;
 }
 else {
 ( ( SCSUData * ) cnv -> extraInfo ) -> locale = lGeneric ;
 }
 _SCSUReset ( cnv , UCNV_RESET_BOTH ) ;
 }
 else {
 * pErrorCode = U_MEMORY_ALLOCATION_ERROR ;
 }
 cnv -> subUChars [ 0 ] = 0xfffd ;
 cnv -> subCharLen = - 1 ;
 }