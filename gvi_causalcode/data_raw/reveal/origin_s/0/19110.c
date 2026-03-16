static void U_CALLCONV _UTF16LEOpen ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * pErrorCode ) {
 ( void ) pArgs ;
 if ( UCNV_GET_VERSION ( cnv ) <= 1 ) {
 _UTF16LEReset ( cnv , UCNV_RESET_BOTH ) ;
 }
 else {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }