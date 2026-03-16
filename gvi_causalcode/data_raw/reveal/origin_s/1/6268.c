static void _UTF16LEOpen ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * pErrorCode ) {
 if ( UCNV_GET_VERSION ( cnv ) <= 1 ) {
 _UTF16LEReset ( cnv , UCNV_RESET_BOTH ) ;
 }
 else {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }