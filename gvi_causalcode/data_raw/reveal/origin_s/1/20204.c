static int32_t u_scanf_ustring_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 UChar * arg = ( UChar * ) ( args [ 0 ] . ptrValue ) ;
 UChar * alias = arg ;
 int32_t count ;
 int32_t skipped = 0 ;
 UChar c ;
 UBool isNotEOF = FALSE ;
 if ( info -> fIsString ) {
 skipped = u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 }
 count = 0 ;
 while ( ( info -> fWidth == - 1 || count < info -> fWidth ) && ( isNotEOF = ufile_getch ( input , & c ) ) && ( ! info -> fIsString || ( c != info -> fPadChar && ! u_isWhitespace ( c ) ) ) ) {
 if ( ! info -> fSkipArg ) {
 * alias ++ = c ;
 }
 ++ count ;
 }
 if ( ! info -> fSkipArg ) {
 if ( ( info -> fWidth == - 1 || count < info -> fWidth ) && isNotEOF ) {
 u_fungetc ( c , input ) ;
 }
 if ( info -> fIsString ) {
 * alias = 0x0000 ;
 }
 }
 * argConverted = ! info -> fSkipArg ;
 return count + skipped ;
 }