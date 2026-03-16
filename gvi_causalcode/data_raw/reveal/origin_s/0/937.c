static void u_printf_set_sign ( UNumberFormat * format , const u_printf_spec_info * info , UChar * prefixBuffer , int32_t * prefixBufLen , UErrorCode * status ) {
 if ( info -> fShowSign ) {
 * prefixBufLen = unum_getTextAttribute ( format , UNUM_POSITIVE_PREFIX , prefixBuffer , * prefixBufLen , status ) ;
 if ( info -> fSpace ) {
 unum_setTextAttribute ( format , UNUM_POSITIVE_PREFIX , gSpaceStr , 1 , status ) ;
 }
 else {
 UChar plusSymbol [ UPRINTF_SYMBOL_BUFFER_SIZE ] ;
 int32_t symbolLen ;
 symbolLen = unum_getSymbol ( format , UNUM_PLUS_SIGN_SYMBOL , plusSymbol , UPRV_LENGTHOF ( plusSymbol ) , status ) ;
 unum_setTextAttribute ( format , UNUM_POSITIVE_PREFIX , plusSymbol , symbolLen , status ) ;
 }
 }
 else {
 * prefixBufLen = 0 ;
 }
 }