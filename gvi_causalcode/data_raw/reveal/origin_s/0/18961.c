static int32_t u_printf_integer_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 int64_t num = args [ 0 ] . int64Value ;
 UNumberFormat * format ;
 UChar result [ UPRINTF_BUFFER_SIZE ] ;
 UChar prefixBuffer [ UPRINTF_BUFFER_SIZE ] ;
 int32_t prefixBufferLen = sizeof ( prefixBuffer ) ;
 int32_t minDigits = - 1 ;
 int32_t resultLen ;
 UErrorCode status = U_ZERO_ERROR ;
 prefixBuffer [ 0 ] = 0 ;
 if ( info -> fIsShort ) num = ( int16_t ) num ;
 else if ( ! info -> fIsLongLong ) num = ( int32_t ) num ;
 format = u_locbund_getNumberFormat ( formatBundle , UNUM_DECIMAL ) ;
 if ( format == 0 ) return 0 ;
 if ( info -> fPrecision != - 1 ) {
 minDigits = unum_getAttribute ( format , UNUM_MIN_INTEGER_DIGITS ) ;
 unum_setAttribute ( format , UNUM_MIN_INTEGER_DIGITS , info -> fPrecision ) ;
 }
 if ( info -> fShowSign ) {
 u_printf_set_sign ( format , info , prefixBuffer , & prefixBufferLen , & status ) ;
 }
 resultLen = unum_formatInt64 ( format , num , result , UPRINTF_BUFFER_SIZE , 0 , & status ) ;
 if ( U_FAILURE ( status ) ) {
 resultLen = 0 ;
 }
 if ( minDigits != - 1 ) {
 unum_setAttribute ( format , UNUM_MIN_INTEGER_DIGITS , minDigits ) ;
 }
 if ( info -> fShowSign ) {
 UErrorCode localStatus = U_ZERO_ERROR ;
 u_printf_reset_sign ( format , info , prefixBuffer , & prefixBufferLen , & localStatus ) ;
 }
 return handler -> pad_and_justify ( context , info , result , resultLen ) ;
 }