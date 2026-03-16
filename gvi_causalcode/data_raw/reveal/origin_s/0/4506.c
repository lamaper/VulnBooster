static enum ETokenType getStringToken ( UCHARBUF * buf , UChar32 initialChar , struct UString * token , UErrorCode * status ) {
 UBool lastStringWasQuoted ;
 UChar32 c ;
 UChar target [ 3 ] = {
 '\0' }
 ;
 UChar * pTarget = target ;
 int len = 0 ;
 UBool isFollowingCharEscaped = FALSE ;
 UBool isNLUnescaped = FALSE ;
 UChar32 prevC = 0 ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 lastStringWasQuoted = FALSE ;
 c = initialChar ;
 ustr_setlen ( token , 0 , status ) ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 for ( ;
 ;
 ) {
 if ( c == QUOTE ) {
 if ( ! lastStringWasQuoted && token -> fLength > 0 ) {
 ustr_ucat ( token , SPACE , status ) ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 }
 lastStringWasQuoted = TRUE ;
 for ( ;
 ;
 ) {
 c = ucbuf_getc ( buf , status ) ;
 if ( c == U_EOF ) {
 return TOK_EOF ;
 }
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 if ( c == QUOTE && ! isFollowingCharEscaped ) {
 break ;
 }
 if ( c == ESCAPE && ! isFollowingCharEscaped ) {
 pTarget = target ;
 c = unescape ( buf , status ) ;
 if ( c == U_ERR ) {
 return TOK_ERROR ;
 }
 if ( c == CR || c == LF ) {
 isNLUnescaped = TRUE ;
 }
 }
 if ( c == ESCAPE && ! isFollowingCharEscaped ) {
 isFollowingCharEscaped = TRUE ;
 }
 else {
 U_APPEND_CHAR32 ( c , pTarget , len ) ;
 pTarget = target ;
 ustr_uscat ( token , pTarget , len , status ) ;
 isFollowingCharEscaped = FALSE ;
 len = 0 ;
 if ( c == CR || c == LF ) {
 if ( isNLUnescaped == FALSE && prevC != CR ) {
 lineCount ++ ;
 }
 isNLUnescaped = FALSE ;
 }
 }
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 prevC = c ;
 }
 }
 else {
 if ( token -> fLength > 0 ) {
 ustr_ucat ( token , SPACE , status ) ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 }
 if ( lastStringWasQuoted ) {
 if ( getShowWarning ( ) ) {
 warning ( lineCount , "Mixing quoted and unquoted strings" ) ;
 }
 if ( isStrict ( ) ) {
 return TOK_ERROR ;
 }
 }
 lastStringWasQuoted = FALSE ;
 if ( c == ESCAPE ) {
 pTarget = target ;
 c = unescape ( buf , status ) ;
 if ( c == U_EOF ) {
 return TOK_ERROR ;
 }
 }
 U_APPEND_CHAR32 ( c , pTarget , len ) ;
 pTarget = target ;
 ustr_uscat ( token , pTarget , len , status ) ;
 len = 0 ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 for ( ;
 ;
 ) {
 c = getNextChar ( buf , FALSE , NULL , status ) ;
 if ( c == U_EOF ) {
 ucbuf_ungetc ( c , buf ) ;
 return TOK_STRING ;
 }
 if ( U_FAILURE ( * status ) ) {
 return TOK_STRING ;
 }
 if ( c == QUOTE || c == OPENBRACE || c == CLOSEBRACE || c == COMMA || c == COLON ) {
 ucbuf_ungetc ( c , buf ) ;
 break ;
 }
 if ( isWhitespace ( c ) ) {
 break ;
 }
 if ( c == ESCAPE ) {
 pTarget = target ;
 c = unescape ( buf , status ) ;
 if ( c == U_ERR ) {
 return TOK_ERROR ;
 }
 }
 U_APPEND_CHAR32 ( c , pTarget , len ) ;
 pTarget = target ;
 ustr_uscat ( token , pTarget , len , status ) ;
 len = 0 ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_ERROR ;
 }
 }
 }
 c = getNextChar ( buf , TRUE , NULL , status ) ;
 if ( U_FAILURE ( * status ) ) {
 return TOK_STRING ;
 }
 if ( c == OPENBRACE || c == CLOSEBRACE || c == COMMA || c == COLON ) {
 ucbuf_ungetc ( c , buf ) ;
 return TOK_STRING ;
 }
 }
 }