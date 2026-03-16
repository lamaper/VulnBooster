static int32_t u_scanf_uchar_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 if ( info -> fWidth < 0 ) {
 info -> fWidth = 1 ;
 }
 info -> fIsString = FALSE ;
 return u_scanf_ustring_handler ( input , info , args , fmt , fmtConsumed , argConverted ) ;
 }