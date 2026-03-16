static UChar32 _UTF16GetNextUChar ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 switch ( pArgs -> converter -> mode ) {
 case 8 : return _UTF16BEGetNextUChar ( pArgs , pErrorCode ) ;
 case 9 : return _UTF16LEGetNextUChar ( pArgs , pErrorCode ) ;
 default : return UCNV_GET_NEXT_UCHAR_USE_TO_U ;
 }
 }