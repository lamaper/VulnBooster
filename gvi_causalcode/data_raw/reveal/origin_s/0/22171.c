static int32_t u_printf_uinteger_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 int64_t num = args [ 0 ] . int64Value ;
 UNumberFormat * format ;
 UChar result [ UPRINTF_BUFFER_SIZE ] ;
 int32_t minDigits = - 1 ;
 int32_t resultLen ;
 UErrorCode status = U_ZERO_ERROR ;
 if ( info -> fIsShort ) num &= UINT16_MAX ;
 else if ( ! info -> fIsLongLong ) num &= UINT32_MAX ;
 format = u_locbund_getNumberFormat ( formatBundle , UNUM_DECIMAL ) ;
 if ( format == 0 ) return 0 ;
 if ( info -> fPrecision != - 1 ) {
 minDigits = unum_getAttribute ( format , UNUM_MIN_INTEGER_DIGITS ) ;
 unum_setAttribute ( format , UNUM_MIN_INTEGER_DIGITS , info -> fPrecision ) ;
 }
 resultLen = unum_formatInt64 ( format , num , result , UPRINTF_BUFFER_SIZE , 0 , & status ) ;
 if ( U_FAILURE ( status ) ) {
 resultLen = 0 ;
 }
 if ( minDigits != - 1 ) {
 unum_setAttribute ( format , UNUM_MIN_INTEGER_DIGITS , minDigits ) ;
 }
 return handler -> pad_and_justify ( context , info , result , resultLen ) ;
 }