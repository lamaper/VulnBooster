static void seekUntilNewline ( UCHARBUF * buf , struct UString * token , UErrorCode * status ) {
 UChar32 c ;
 if ( U_FAILURE ( * status ) ) {
 return ;
 }
 do {
 c = ucbuf_getc ( buf , status ) ;
 if ( token != NULL ) {
 ustr_u32cat ( token , c , status ) ;
 }
 }
 while ( ! isNewline ( c ) && c != U_EOF && * status == U_ZERO_ERROR ) ;
 }