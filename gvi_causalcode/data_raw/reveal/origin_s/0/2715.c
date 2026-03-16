static void u_printf_reset_sign ( UNumberFormat * format , const u_printf_spec_info * info , UChar * prefixBuffer , int32_t * prefixBufLen , UErrorCode * status ) {
 if ( info -> fShowSign ) {
 unum_setTextAttribute ( format , UNUM_POSITIVE_PREFIX , prefixBuffer , * prefixBufLen , status ) ;
 }
 }