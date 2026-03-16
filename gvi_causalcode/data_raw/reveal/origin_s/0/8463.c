static int32_t u_scanf_percent_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 ( void ) fmt ;
 ( void ) fmtConsumed ;
 int32_t len ;
 double num ;
 UNumberFormat * format ;
 int32_t parsePos = 0 ;
 UErrorCode status = U_ZERO_ERROR ;
 u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 ufile_fill_uchar_buffer ( input ) ;
 len = ( int32_t ) ( input -> str . fLimit - input -> str . fPos ) ;
 if ( info -> fWidth != - 1 ) len = ufmt_min ( len , info -> fWidth ) ;
 format = u_locbund_getNumberFormat ( & input -> str . fBundle , UNUM_PERCENT ) ;
 if ( format == 0 ) return 0 ;
 u_scanf_skip_leading_positive_sign ( input , format , & status ) ;
 num = unum_parseDouble ( format , input -> str . fPos , len , & parsePos , & status ) ;
 if ( ! info -> fSkipArg ) {
 * ( double * ) ( args [ 0 ] . ptrValue ) = num ;
 }
 input -> str . fPos += parsePos ;
 * argConverted = ! info -> fSkipArg ;
 return parsePos ;
 }