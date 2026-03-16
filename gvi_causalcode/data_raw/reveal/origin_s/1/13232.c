static int32_t u_scanf_pointer_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 int32_t len ;
 int32_t skipped ;
 void * result ;
 void * * p = ( void * * ) ( args [ 0 ] . ptrValue ) ;
 skipped = u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 ufile_fill_uchar_buffer ( input ) ;
 len = ( int32_t ) ( input -> str . fLimit - input -> str . fPos ) ;
 if ( info -> fWidth != - 1 ) {
 len = ufmt_min ( len , info -> fWidth ) ;
 }
 if ( len > ( int32_t ) ( sizeof ( void * ) * 2 ) ) {
 len = ( int32_t ) ( sizeof ( void * ) * 2 ) ;
 }
 result = ufmt_utop ( input -> str . fPos , & len ) ;
 if ( ! info -> fSkipArg ) {
 * p = result ;
 }
 input -> str . fPos += len ;
 * argConverted = ! info -> fSkipArg ;
 return len + skipped ;
 }