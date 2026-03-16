static int32_t u_scanf_count_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 ( void ) input ;
 ( void ) fmt ;
 ( void ) fmtConsumed ;
 if ( ! info -> fSkipArg ) {
 if ( info -> fIsShort ) * ( int16_t * ) ( args [ 0 ] . ptrValue ) = ( int16_t ) ( UINT16_MAX & info -> fWidth ) ;
 else if ( info -> fIsLongLong ) * ( int64_t * ) ( args [ 0 ] . ptrValue ) = info -> fWidth ;
 else * ( int32_t * ) ( args [ 0 ] . ptrValue ) = ( int32_t ) ( UINT32_MAX & info -> fWidth ) ;
 }
 * argConverted = 0 ;
 return 0 ;
 }