static int32_t u_scanf_scientific_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 ( void ) fmt ;
 ( void ) fmtConsumed ;
 int32_t len ;
 double num ;
 UNumberFormat * format ;
 int32_t parsePos = 0 ;
 int32_t skipped ;
 UErrorCode status = U_ZERO_ERROR ;
 UChar srcExpBuf [ UPRINTF_SYMBOL_BUFFER_SIZE ] ;
 int32_t srcLen , expLen ;
 UChar expBuf [ UPRINTF_SYMBOL_BUFFER_SIZE ] ;
 skipped = u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 ufile_fill_uchar_buffer ( input ) ;
 len = ( int32_t ) ( input -> str . fLimit - input -> str . fPos ) ;
 if ( info -> fWidth != - 1 ) len = ufmt_min ( len , info -> fWidth ) ;
 format = u_locbund_getNumberFormat ( & input -> str . fBundle , UNUM_SCIENTIFIC ) ;
 if ( format == 0 ) return 0 ;
 srcLen = unum_getSymbol ( format , UNUM_EXPONENTIAL_SYMBOL , srcExpBuf , sizeof ( srcExpBuf ) , & status ) ;
 if ( info -> fSpec == ( UChar ) 0x65 ) {
 expLen = u_strToLower ( expBuf , ( int32_t ) sizeof ( expBuf ) , srcExpBuf , srcLen , input -> str . fBundle . fLocale , & status ) ;
 }
 else {
 expLen = u_strToUpper ( expBuf , ( int32_t ) sizeof ( expBuf ) , srcExpBuf , srcLen , input -> str . fBundle . fLocale , & status ) ;
 }
 unum_setSymbol ( format , UNUM_EXPONENTIAL_SYMBOL , expBuf , expLen , & status ) ;
 skipped += u_scanf_skip_leading_positive_sign ( input , format , & status ) ;
 num = unum_parseDouble ( format , input -> str . fPos , len , & parsePos , & status ) ;
 if ( ! info -> fSkipArg ) {
 if ( info -> fIsLong ) * ( double * ) ( args [ 0 ] . ptrValue ) = num ;
 else if ( info -> fIsLongDouble ) * ( long double * ) ( args [ 0 ] . ptrValue ) = num ;
 else * ( float * ) ( args [ 0 ] . ptrValue ) = ( float ) num ;
 }
 input -> str . fPos += parsePos ;
 * argConverted = ! info -> fSkipArg ;
 return parsePos + skipped ;
 }