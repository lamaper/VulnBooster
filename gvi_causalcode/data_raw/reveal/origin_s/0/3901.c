static int32_t u_scanf_uinteger_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 return u_scanf_integer_handler ( input , info , args , fmt , fmtConsumed , argConverted ) ;
 }