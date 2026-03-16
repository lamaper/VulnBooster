static void _HZOpen ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * errorCode ) {
 UConverter * gbConverter ;
 if ( pArgs -> onlyTestIsLoadable ) {
 ucnv_canCreateConverter ( "GBK" , errorCode ) ;
 return ;
 }
 gbConverter = ucnv_open ( "GBK" , errorCode ) ;
 if ( U_FAILURE ( * errorCode ) ) {
 return ;
 }
 cnv -> toUnicodeStatus = 0 ;
 cnv -> fromUnicodeStatus = 0 ;
 cnv -> mode = 0 ;
 cnv -> fromUChar32 = 0x0000 ;
 cnv -> extraInfo = uprv_calloc ( 1 , sizeof ( UConverterDataHZ ) ) ;
 if ( cnv -> extraInfo != NULL ) {
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> gbConverter = gbConverter ;
 }
 else {
 ucnv_close ( gbConverter ) ;
 * errorCode = U_MEMORY_ALLOCATION_ERROR ;
 return ;
 }
 }