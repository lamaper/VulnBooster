static int32_t u_scanf_scidbl_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 ( void ) fmt ;
 ( void ) fmtConsumed ;
 int32_t len ;
 double num ;
 UNumberFormat * scientificFormat , * genericFormat ;
 double scientificResult , genericResult ;
 int32_t scientificParsePos = 0 , genericParsePos = 0 , parsePos = 0 ;
 int32_t skipped ;
 UErrorCode scientificStatus = U_ZERO_ERROR ;
 UErrorCode genericStatus = U_ZERO_ERROR ;
 skipped = u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 ufile_fill_uchar_buffer ( input ) ;
 len = ( int32_t ) ( input -> str . fLimit - input -> str . fPos ) ;
 if ( info -> fWidth != - 1 ) len = ufmt_min ( len , info -> fWidth ) ;
 scientificFormat = u_locbund_getNumberFormat ( & input -> str . fBundle , UNUM_SCIENTIFIC ) ;
 genericFormat = u_locbund_getNumberFormat ( & input -> str . fBundle , UNUM_DECIMAL ) ;
 if ( scientificFormat == 0 || genericFormat == 0 ) return 0 ;
 skipped += u_scanf_skip_leading_positive_sign ( input , genericFormat , & genericStatus ) ;
 scientificResult = unum_parseDouble ( scientificFormat , input -> str . fPos , len , & scientificParsePos , & scientificStatus ) ;
 genericResult = unum_parseDouble ( genericFormat , input -> str . fPos , len , & genericParsePos , & genericStatus ) ;
 if ( scientificParsePos > genericParsePos ) {
 num = scientificResult ;
 parsePos += scientificParsePos ;
 }
 else {
 num = genericResult ;
 parsePos += genericParsePos ;
 }
 input -> str . fPos += parsePos ;
 if ( ! info -> fSkipArg ) {
 if ( info -> fIsLong ) * ( double * ) ( args [ 0 ] . ptrValue ) = num ;
 else if ( info -> fIsLongDouble ) * ( long double * ) ( args [ 0 ] . ptrValue ) = num ;
 else * ( float * ) ( args [ 0 ] . ptrValue ) = ( float ) num ;
 }
 * argConverted = ! info -> fSkipArg ;
 return parsePos + skipped ;
 }