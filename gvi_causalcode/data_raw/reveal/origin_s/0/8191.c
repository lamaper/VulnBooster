static UChar32 getNextChar ( UCHARBUF * buf , UBool skipwhite , struct UString * token , UErrorCode * status ) {
 UChar32 c , c2 ;
 if ( U_FAILURE ( * status ) ) {
 return U_EOF ;
 }
 for ( ;
 ;
 ) {
 c = ucbuf_getc ( buf , status ) ;
 if ( c == U_EOF ) {
 return U_EOF ;
 }
 if ( skipwhite && isWhitespace ( c ) ) {
 continue ;
 }
 if ( c != SLASH ) {
 return c ;
 }
 c = ucbuf_getc ( buf , status ) ;
 if ( c == U_EOF ) {
 return U_EOF ;
 }
 switch ( c ) {
 case SLASH : seekUntilNewline ( buf , NULL , status ) ;
 break ;
 case ASTERISK : c2 = ucbuf_getc ( buf , status ) ;
 if ( c2 == ASTERISK ) {
 seekUntilEndOfComment ( buf , token , status ) ;
 }
 else {
 ucbuf_ungetc ( c2 , buf ) ;
 seekUntilEndOfComment ( buf , NULL , status ) ;
 }
 break ;
 default : ucbuf_ungetc ( c , buf ) ;
 return SLASH ;
 }
 }
 }