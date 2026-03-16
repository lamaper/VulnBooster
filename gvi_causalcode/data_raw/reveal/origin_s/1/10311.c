static void _UTF7Open ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * pErrorCode ) {
 if ( UCNV_GET_VERSION ( cnv ) <= 1 ) {
 cnv -> fromUnicodeStatus = UCNV_GET_VERSION ( cnv ) << 28 ;
 _UTF7Reset ( cnv , UCNV_RESET_BOTH ) ;
 }
 else {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }