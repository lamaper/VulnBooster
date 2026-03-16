static int32_t u_scanf_scanset_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 USet * scanset ;
 UErrorCode status = U_ZERO_ERROR ;
 int32_t chLeft = INT32_MAX ;
 UChar32 c ;
 UChar * alias = ( UChar * ) ( args [ 0 ] . ptrValue ) ;
 UBool isNotEOF = FALSE ;
 UBool readCharacter = FALSE ;
 scanset = uset_open ( 0 , - 1 ) ;
 fmt -- ;
 if ( info -> fWidth >= 0 ) {
 chLeft = info -> fWidth ;
 }
 * fmtConsumed = uset_applyPattern ( scanset , fmt , - 1 , 0 , & status ) ;
 if ( U_SUCCESS ( status ) ) {
 c = 0 ;
 while ( chLeft > 0 ) {
 if ( ( isNotEOF = ufile_getch32 ( input , & c ) ) && uset_contains ( scanset , c ) ) {
 readCharacter = TRUE ;
 if ( ! info -> fSkipArg ) {
 int32_t idx = 0 ;
 UBool isError = FALSE ;
 U16_APPEND ( alias , idx , chLeft , c , isError ) ;
 if ( isError ) {
 break ;
 }
 alias += idx ;
 }
 chLeft -= ( 1 + U_IS_SUPPLEMENTARY ( c ) ) ;
 }
 else {
 break ;
 }
 }
 if ( isNotEOF && chLeft > 0 ) {
 u_fungetc ( c , input ) ;
 }
 }
 uset_close ( scanset ) ;
 if ( ! readCharacter ) return - 1 ;
 else if ( ! info -> fSkipArg ) {
 * alias = 0x00 ;
 }
 * argConverted = ! info -> fSkipArg ;
 return ( info -> fWidth >= 0 ? info -> fWidth : INT32_MAX ) - chLeft ;
 }