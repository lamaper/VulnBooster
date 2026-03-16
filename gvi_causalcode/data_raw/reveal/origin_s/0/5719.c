static void _reset ( UConverter * converter , UConverterResetChoice choice , UBool callCallback ) {
 if ( converter == NULL ) {
 return ;
 }
 if ( callCallback ) {
 UErrorCode errorCode ;
 if ( choice <= UCNV_RESET_TO_UNICODE && converter -> fromCharErrorBehaviour != UCNV_TO_U_DEFAULT_CALLBACK ) {
 UConverterToUnicodeArgs toUArgs = {
 sizeof ( UConverterToUnicodeArgs ) , TRUE , NULL , NULL , NULL , NULL , NULL , NULL }
 ;
 toUArgs . converter = converter ;
 errorCode = U_ZERO_ERROR ;
 converter -> fromCharErrorBehaviour ( converter -> toUContext , & toUArgs , NULL , 0 , UCNV_RESET , & errorCode ) ;
 }
 if ( choice != UCNV_RESET_TO_UNICODE && converter -> fromUCharErrorBehaviour != UCNV_FROM_U_DEFAULT_CALLBACK ) {
 UConverterFromUnicodeArgs fromUArgs = {
 sizeof ( UConverterFromUnicodeArgs ) , TRUE , NULL , NULL , NULL , NULL , NULL , NULL }
 ;
 fromUArgs . converter = converter ;
 errorCode = U_ZERO_ERROR ;
 converter -> fromUCharErrorBehaviour ( converter -> fromUContext , & fromUArgs , NULL , 0 , 0 , UCNV_RESET , & errorCode ) ;
 }
 }
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 converter -> toUnicodeStatus = converter -> sharedData -> toUnicodeStatus ;
 converter -> mode = 0 ;
 converter -> toULength = 0 ;
 converter -> invalidCharLength = converter -> UCharErrorBufferLength = 0 ;
 converter -> preToULength = 0 ;
 }
 if ( choice != UCNV_RESET_TO_UNICODE ) {
 converter -> fromUnicodeStatus = 0 ;
 converter -> fromUChar32 = 0 ;
 converter -> invalidUCharLength = converter -> charErrorBufferLength = 0 ;
 converter -> preFromUFirstCP = U_SENTINEL ;
 converter -> preFromULength = 0 ;
 }
 if ( converter -> sharedData -> impl -> reset != NULL ) {
 converter -> sharedData -> impl -> reset ( converter , choice ) ;
 }
 }