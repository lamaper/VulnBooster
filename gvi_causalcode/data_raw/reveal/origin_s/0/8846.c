static void U_CALLCONV _UTF32Open ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * pErrorCode ) {
 ( void ) pArgs ;
 ( void ) pErrorCode ;
 _UTF32Reset ( cnv , UCNV_RESET_BOTH ) ;
 }