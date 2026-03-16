static int32_t u_scanf_string_handler ( UFILE * input , u_scanf_spec_info * info , ufmt_args * args , const UChar * fmt , int32_t * fmtConsumed , int32_t * argConverted ) {
 const UChar * source ;
 UConverter * conv ;
 char * arg = ( char * ) ( args [ 0 ] . ptrValue ) ;
 char * alias = arg ;
 char * limit ;
 UErrorCode status = U_ZERO_ERROR ;
 int32_t count ;
 int32_t skipped = 0 ;
 UChar c ;
 UBool isNotEOF = FALSE ;
 if ( info -> fIsString ) {
 skipped = u_scanf_skip_leading_ws ( input , info -> fPadChar ) ;
 }
 count = 0 ;
 conv = u_getDefaultConverter ( & status ) ;
 if ( U_FAILURE ( status ) ) return - 1 ;
 while ( ( info -> fWidth == - 1 || count < info -> fWidth ) && ( isNotEOF = ufile_getch ( input , & c ) ) && ( ! info -> fIsString || ( c != info -> fPadChar && ! u_isWhitespace ( c ) ) ) ) {
 if ( ! info -> fSkipArg ) {
 source = & c ;
 if ( info -> fWidth > 0 ) {
 limit = alias + info -> fWidth - count ;
 }
 else {
 limit = alias + ucnv_getMaxCharSize ( conv ) ;
 }
 ucnv_fromUnicode ( conv , & alias , limit , & source , source + 1 , NULL , TRUE , & status ) ;
 if ( U_FAILURE ( status ) ) {
 u_releaseDefaultConverter ( conv ) ;
 return - 1 ;
 }
 }
 ++ count ;
 }
 if ( ! info -> fSkipArg ) {
 if ( ( info -> fWidth == - 1 || count < info -> fWidth ) && isNotEOF ) u_fungetc ( c , input ) ;
 if ( info -> fIsString ) {
 * alias = 0x00 ;
 }
 }
 u_releaseDefaultConverter ( conv ) ;
 * argConverted = ! info -> fSkipArg ;
 return count + skipped ;
 }