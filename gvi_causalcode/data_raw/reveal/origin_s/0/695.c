static celt element ( struct vars * v , const chr * startp , const chr * endp ) {
 const struct cname * cn ;
 size_t len ;
 assert ( startp < endp ) ;
 len = endp - startp ;
 if ( len == 1 ) return * startp ;
 NOTE ( REG_ULOCALE ) ;
 for ( cn = cnames ;
 cn -> name != NULL ;
 cn ++ ) {
 if ( strlen ( cn -> name ) == len && pg_char_and_wchar_strncmp ( cn -> name , startp , len ) == 0 ) {
 break ;
 }
 }
 if ( cn -> name != NULL ) return CHR ( cn -> code ) ;
 ERR ( REG_ECOLLATE ) ;
 return 0 ;
 }