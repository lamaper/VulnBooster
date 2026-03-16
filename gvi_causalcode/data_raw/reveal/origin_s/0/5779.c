static int32_t u_scanf_simple_percent_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 ( void ) info ;
 ( void ) args ;
 ( void ) fmt ;
 ( void ) fmtConsumed ;
 * argConverted = 0 ;
 if ( u_fgetc ( input ) != 0x0025 ) {
 * argConverted = - 1 ;
 }
 return 1 ;
 }