static UChar32 U_CALLCONV _UTF32GetNextUChar ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 switch ( pArgs -> converter -> mode ) {
 case 8 : return T_UConverter_getNextUChar_UTF32_BE ( pArgs , pErrorCode ) ;
 case 9 : return T_UConverter_getNextUChar_UTF32_LE ( pArgs , pErrorCode ) ;
 default : return UCNV_GET_NEXT_UCHAR_USE_TO_U ;
 }
 }