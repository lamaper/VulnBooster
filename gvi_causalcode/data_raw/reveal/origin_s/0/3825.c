static int32_t u_scanf_skip_leading_positive_sign ( UFILE * input , UNumberFormat * format , UErrorCode * status ) {
 UChar c ;
 int32_t count = 0 ;
 UBool isNotEOF ;
 UChar plusSymbol [ USCANF_SYMBOL_BUFFER_SIZE ] ;
 int32_t symbolLen ;
 UErrorCode localStatus = U_ZERO_ERROR ;
 if ( U_SUCCESS ( * status ) ) {
 symbolLen = unum_getSymbol ( format , UNUM_PLUS_SIGN_SYMBOL , plusSymbol , UPRV_LENGTHOF ( plusSymbol ) , & localStatus ) ;
 if ( U_SUCCESS ( localStatus ) ) {
 while ( ( isNotEOF = ufile_getch ( input , & c ) ) && ( count < symbolLen && c == plusSymbol [ count ] ) ) {
 count ++ ;
 }
 if ( isNotEOF ) {
 u_fungetc ( c , input ) ;
 }
 }
 }
 return count ;
 }