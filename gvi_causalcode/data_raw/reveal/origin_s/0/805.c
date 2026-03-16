static int32_t u_printf_percent_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 double num = ( double ) ( args [ 0 ] . doubleValue ) ;
 UNumberFormat * format ;
 UChar result [ UPRINTF_BUFFER_SIZE ] ;
 UChar prefixBuffer [ UPRINTF_BUFFER_SIZE ] ;
 int32_t prefixBufferLen = sizeof ( prefixBuffer ) ;
 int32_t minDecimalDigits ;
 int32_t maxDecimalDigits ;
 int32_t resultLen ;
 UErrorCode status = U_ZERO_ERROR ;
 prefixBuffer [ 0 ] = 0 ;
 format = u_locbund_getNumberFormat ( formatBundle , UNUM_PERCENT ) ;
 if ( format == 0 ) return 0 ;
 minDecimalDigits = unum_getAttribute ( format , UNUM_MIN_FRACTION_DIGITS ) ;
 maxDecimalDigits = unum_getAttribute ( format , UNUM_MAX_FRACTION_DIGITS ) ;
 if ( info -> fPrecision != - 1 ) {
 unum_setAttribute ( format , UNUM_FRACTION_DIGITS , info -> fPrecision ) ;
 }
 else if ( info -> fAlt ) {
 unum_setAttribute ( format , UNUM_FRACTION_DIGITS , 6 ) ;
 }
 else {
 unum_setAttribute ( format , UNUM_FRACTION_DIGITS , 6 ) ;
 }
 if ( info -> fShowSign ) {
 u_printf_set_sign ( format , info , prefixBuffer , & prefixBufferLen , & status ) ;
 }
 resultLen = unum_formatDouble ( format , num , result , UPRINTF_BUFFER_SIZE , 0 , & status ) ;
 if ( U_FAILURE ( status ) ) {
 resultLen = 0 ;
 }
 unum_setAttribute ( format , UNUM_MIN_FRACTION_DIGITS , minDecimalDigits ) ;
 unum_setAttribute ( format , UNUM_MAX_FRACTION_DIGITS , maxDecimalDigits ) ;
 if ( info -> fShowSign ) {
 UErrorCode localStatus = U_ZERO_ERROR ;
 u_printf_reset_sign ( format , info , prefixBuffer , & prefixBufferLen , & localStatus ) ;
 }
 return handler -> pad_and_justify ( context , info , result , resultLen ) ;
 }