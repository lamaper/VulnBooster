static int32_t u_scanf_skip_leading_ws ( UFILE * input , UChar pad ) {
 UChar c ;
 int32_t count = 0 ;
 UBool isNotEOF ;
 while ( ( isNotEOF = ufile_getch ( input , & c ) ) && ( c == pad || u_isWhitespace ( c ) ) ) {
 count ++ ;
 }
 if ( isNotEOF ) u_fungetc ( c , input ) ;
 return count ;
 }