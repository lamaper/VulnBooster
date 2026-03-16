static int32_t getCodesFromLocale ( const char * locale , UScriptCode * scripts , int32_t capacity , UErrorCode * err ) {
 UErrorCode internalErrorCode = U_ZERO_ERROR ;
 char lang [ 8 ] ;
 char script [ 8 ] ;
 int32_t scriptLength ;
 if ( U_FAILURE ( * err ) ) {
 return 0 ;
 }
 uloc_getLanguage ( locale , lang , UPRV_LENGTHOF ( lang ) , & internalErrorCode ) ;
 if ( U_FAILURE ( internalErrorCode ) || internalErrorCode == U_STRING_NOT_TERMINATED_WARNING ) {
 return 0 ;
 }
 if ( 0 == uprv_strcmp ( lang , "ja" ) ) {
 return setCodes ( JAPANESE , UPRV_LENGTHOF ( JAPANESE ) , scripts , capacity , err ) ;
 }
 if ( 0 == uprv_strcmp ( lang , "ko" ) ) {
 return setCodes ( KOREAN , UPRV_LENGTHOF ( KOREAN ) , scripts , capacity , err ) ;
 }
 scriptLength = uloc_getScript ( locale , script , UPRV_LENGTHOF ( script ) , & internalErrorCode ) ;
 if ( U_FAILURE ( internalErrorCode ) || internalErrorCode == U_STRING_NOT_TERMINATED_WARNING ) {
 return 0 ;
 }
 if ( 0 == uprv_strcmp ( lang , "zh" ) && 0 == uprv_strcmp ( script , "Hant" ) ) {
 return setCodes ( HAN_BOPO , UPRV_LENGTHOF ( HAN_BOPO ) , scripts , capacity , err ) ;
 }
 if ( scriptLength != 0 ) {
 UScriptCode scriptCode = ( UScriptCode ) u_getPropertyValueEnum ( UCHAR_SCRIPT , script ) ;
 if ( scriptCode != USCRIPT_INVALID_CODE ) {
 if ( scriptCode == USCRIPT_SIMPLIFIED_HAN || scriptCode == USCRIPT_TRADITIONAL_HAN ) {
 scriptCode = USCRIPT_HAN ;
 }
 return setOneCode ( scriptCode , scripts , capacity , err ) ;
 }
 }
 return 0 ;
 }