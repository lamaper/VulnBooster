static char * prepare_word_match ( const byte * name ) {
 byte * pattern , * p ;
 int c ;
 p = pattern = xmalloc ( strlen ( name ) + 1 ) ;
 do {
 while ( * name && ! word_match_chars [ * name ] ) name ++ ;
 for ( ;
 * name && ( c = word_match_chars [ * name ] ) ;
 name ++ ) * p ++ = c ;
 * p ++ = ' ' ;
 }
 while ( * name ) ;
 p [ - 1 ] = 0 ;
 return pattern ;
 }