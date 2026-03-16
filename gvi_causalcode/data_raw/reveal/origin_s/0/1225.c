static struct cvec * cclass ( struct vars * v , const chr * startp , const chr * endp , int cases ) {
 size_t len ;
 struct cvec * cv = NULL ;
 const char * const * namePtr ;
 int i , index ;
 static const char * const classNames [ ] = {
 "alnum" , "alpha" , "ascii" , "blank" , "cntrl" , "digit" , "graph" , "lower" , "print" , "punct" , "space" , "upper" , "xdigit" , NULL }
 ;
 enum classes {
 CC_ALNUM , CC_ALPHA , CC_ASCII , CC_BLANK , CC_CNTRL , CC_DIGIT , CC_GRAPH , CC_LOWER , CC_PRINT , CC_PUNCT , CC_SPACE , CC_UPPER , CC_XDIGIT }
 ;
 len = endp - startp ;
 index = - 1 ;
 for ( namePtr = classNames , i = 0 ;
 * namePtr != NULL ;
 namePtr ++ , i ++ ) {
 if ( strlen ( * namePtr ) == len && pg_char_and_wchar_strncmp ( * namePtr , startp , len ) == 0 ) {
 index = i ;
 break ;
 }
 }
 if ( index == - 1 ) {
 ERR ( REG_ECTYPE ) ;
 return NULL ;
 }
 if ( cases && ( ( enum classes ) index == CC_LOWER || ( enum classes ) index == CC_UPPER ) ) index = ( int ) CC_ALPHA ;
 switch ( ( enum classes ) index ) {
 case CC_PRINT : cv = pg_ctype_get_cache ( pg_wc_isprint ) ;
 break ;
 case CC_ALNUM : cv = pg_ctype_get_cache ( pg_wc_isalnum ) ;
 break ;
 case CC_ALPHA : cv = pg_ctype_get_cache ( pg_wc_isalpha ) ;
 break ;
 case CC_ASCII : cv = getcvec ( v , 0 , 1 ) ;
 if ( cv ) addrange ( cv , 0 , 0x7f ) ;
 break ;
 case CC_BLANK : cv = getcvec ( v , 2 , 0 ) ;
 addchr ( cv , '\t' ) ;
 addchr ( cv , ' ' ) ;
 break ;
 case CC_CNTRL : cv = getcvec ( v , 0 , 2 ) ;
 addrange ( cv , 0x0 , 0x1f ) ;
 addrange ( cv , 0x7f , 0x9f ) ;
 break ;
 case CC_DIGIT : cv = pg_ctype_get_cache ( pg_wc_isdigit ) ;
 break ;
 case CC_PUNCT : cv = pg_ctype_get_cache ( pg_wc_ispunct ) ;
 break ;
 case CC_XDIGIT : cv = getcvec ( v , 0 , 3 ) ;
 if ( cv ) {
 addrange ( cv , '0' , '9' ) ;
 addrange ( cv , 'a' , 'f' ) ;
 addrange ( cv , 'A' , 'F' ) ;
 }
 break ;
 case CC_SPACE : cv = pg_ctype_get_cache ( pg_wc_isspace ) ;
 break ;
 case CC_LOWER : cv = pg_ctype_get_cache ( pg_wc_islower ) ;
 break ;
 case CC_UPPER : cv = pg_ctype_get_cache ( pg_wc_isupper ) ;
 break ;
 case CC_GRAPH : cv = pg_ctype_get_cache ( pg_wc_isgraph ) ;
 break ;
 }
 if ( cv == NULL ) ERR ( REG_ESPACE ) ;
 return cv ;
 }