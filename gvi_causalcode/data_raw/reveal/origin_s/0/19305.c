static int32_t u_scanf_integer_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 ( void ) fmt ;
 ( void ) fmtConsumed ;
 int32_t len ;
 void * num = ( void * ) ( args [ 0 ] . ptrValue ) ;
 UNumberFormat * format ;
 int32_t parsePos = 0 ;
 int32_t skipped ;
 UErrorCode status = U_ZERO_ERROR ;
 int64_t result ;
 skipped = u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 ufile_fill_uchar_buffer ( input ) ;
 len = ( int32_t ) ( input -> str . fLimit - input -> str . fPos ) ;
 if ( info -> fWidth != - 1 ) len = ufmt_min ( len , info -> fWidth ) ;
 format = u_locbund_getNumberFormat ( & input -> str . fBundle , UNUM_DECIMAL ) ;
 if ( format == 0 ) return 0 ;
 skipped += u_scanf_skip_leading_positive_sign ( input , format , & status ) ;
 result = unum_parseInt64 ( format , input -> str . fPos , len , & parsePos , & status ) ;
 if ( ! info -> fSkipArg ) {
 if ( info -> fIsShort ) * ( int16_t * ) num = ( int16_t ) ( UINT16_MAX & result ) ;
 else if ( info -> fIsLongLong ) * ( int64_t * ) num = result ;
 else * ( int32_t * ) num = ( int32_t ) ( UINT32_MAX & result ) ;
 }
 input -> str . fPos += parsePos ;
 * argConverted = ! info -> fSkipArg ;
 return parsePos + skipped ;
 }