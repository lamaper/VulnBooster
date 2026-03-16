static int32_t u_printf_scientific_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 double num = ( double ) ( args [ 0 ] . doubleValue ) ;
 UNumberFormat * format ;
 UChar result [ UPRINTF_BUFFER_SIZE ] ;
 UChar prefixBuffer [ UPRINTF_BUFFER_SIZE ] ;
 int32_t prefixBufferLen = sizeof ( prefixBuffer ) ;
 int32_t minDecimalDigits ;
 int32_t maxDecimalDigits ;
 UErrorCode status = U_ZERO_ERROR ;
 UChar srcExpBuf [ UPRINTF_SYMBOL_BUFFER_SIZE ] ;
 int32_t srcLen , expLen ;
 int32_t resultLen ;
 UChar expBuf [ UPRINTF_SYMBOL_BUFFER_SIZE ] ;
 prefixBuffer [ 0 ] = 0 ;
 format = u_locbund_getNumberFormat ( formatBundle , UNUM_SCIENTIFIC ) ;
 if ( format == 0 ) return 0 ;
 srcLen = unum_getSymbol ( format , UNUM_EXPONENTIAL_SYMBOL , srcExpBuf , sizeof ( srcExpBuf ) , & status ) ;
 if ( info -> fSpec == ( UChar ) 0x65 ) {
 expLen = u_strToLower ( expBuf , ( int32_t ) sizeof ( expBuf ) , srcExpBuf , srcLen , formatBundle -> fLocale , & status ) ;
 }
 else {
 expLen = u_strToUpper ( expBuf , ( int32_t ) sizeof ( expBuf ) , srcExpBuf , srcLen , formatBundle -> fLocale , & status ) ;
 }
 unum_setSymbol ( format , UNUM_EXPONENTIAL_SYMBOL , expBuf , expLen , & status ) ;
 minDecimalDigits = unum_getAttribute ( format , UNUM_MIN_FRACTION_DIGITS ) ;
 maxDecimalDigits = unum_getAttribute ( format , UNUM_MAX_FRACTION_DIGITS ) ;
 if ( info -> fPrecision != - 1 ) {
 if ( info -> fOrigSpec == ( UChar ) 0x65 || info -> fOrigSpec == ( UChar ) 0x45 ) {
 unum_setAttribute ( format , UNUM_FRACTION_DIGITS , info -> fPrecision ) ;
 }
 else {
 unum_setAttribute ( format , UNUM_MIN_FRACTION_DIGITS , 1 ) ;
 unum_setAttribute ( format , UNUM_MAX_FRACTION_DIGITS , info -> fPrecision ) ;
 }
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