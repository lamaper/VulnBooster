static void seekUntilEndOfComment ( UCHARBUF * buf , struct UString * token , UErrorCode * status ) {
 UChar32 c , d ;
 uint32_t line ;
 if ( U_FAILURE ( * status ) ) {
 return ;
 }
 line = lineCount ;
 do {
 c = ucbuf_getc ( buf , status ) ;
 if ( c == ASTERISK ) {
 d = ucbuf_getc ( buf , status ) ;
 if ( d != SLASH ) {
 ucbuf_ungetc ( d , buf ) ;
 }
 else {
 break ;
 }
 }
 if ( token != NULL ) {
 ustr_u32cat ( token , c , status ) ;
 }
 isNewline ( c ) ;
 }
 while ( c != U_EOF && * status == U_ZERO_ERROR ) ;
 if ( c == U_EOF ) {
 * status = U_INVALID_FORMAT_ERROR ;
 error ( line , "unterminated comment detected" ) ;
 }
 }