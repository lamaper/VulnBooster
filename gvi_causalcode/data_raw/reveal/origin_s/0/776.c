static CURLcode glob_parse ( URLGlob * glob , char * pattern , size_t pos , unsigned long * amount ) {
 CURLcode res = CURLE_OK ;
 int globindex = 0 ;
 * amount = 1 ;
 while ( * pattern && ! res ) {
 char * buf = glob -> glob_buffer ;
 size_t sublen = 0 ;
 while ( * pattern && * pattern != '{
' ) {
 if ( * pattern == '[' ) {
 size_t skip ;
 if ( peek_ipv6 ( pattern , & skip ) ) {
 memcpy ( buf , pattern , skip ) ;
 buf += skip ;
 pattern += skip ;
 sublen += skip ;
 continue ;
 }
 break ;
 }
 if ( * pattern == '}
' || * pattern == ']' ) return GLOBERROR ( "unmatched close brace/bracket" , pos , CURLE_URL_MALFORMAT ) ;
 if ( * pattern == '\\' && ( * ( pattern + 1 ) == '{
' || * ( pattern + 1 ) == '[' || * ( pattern + 1 ) == '}
' || * ( pattern + 1 ) == ']' ) ) {
 ++ pattern ;
 ++ pos ;
 }
 * buf ++ = * pattern ++ ;
 ++ pos ;
 sublen ++ ;
 }
 if ( sublen ) {
 * buf = '\0' ;
 res = glob_fixed ( glob , glob -> glob_buffer , sublen ) ;
 }
 else {
 switch ( * pattern ) {
 case '\0' : break ;
 case '{
' : pattern ++ ;
 pos ++ ;
 res = glob_set ( glob , & pattern , & pos , amount , globindex ++ ) ;
 break ;
 case '[' : pattern ++ ;
 pos ++ ;
 res = glob_range ( glob , & pattern , & pos , amount , globindex ++ ) ;
 break ;
 }
 }
 if ( ++ glob -> size >= GLOB_PATTERN_NUM ) return GLOBERROR ( "too many globs" , pos , CURLE_URL_MALFORMAT ) ;
 }
 return res ;
 }