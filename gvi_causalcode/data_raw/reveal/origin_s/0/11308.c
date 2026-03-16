inline void uprv_checkCanGetBuffer ( const icu : : UnicodeString & s , UErrorCode & errorCode ) {
 if ( U_SUCCESS ( errorCode ) && s . isBogus ( ) ) {
 errorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 }