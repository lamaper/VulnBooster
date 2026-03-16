static int word_match ( const byte * uid , size_t uidlen , const byte * pattern ) {
 size_t wlen , n ;
 const byte * p ;
 const byte * s ;
 for ( s = pattern ;
 * s ;
 ) {
 do {
 while ( uidlen && ! word_match_chars [ * uid ] ) uid ++ , uidlen -- ;
 n = uidlen ;
 p = uid ;
 while ( n && word_match_chars [ * p ] ) p ++ , n -- ;
 wlen = p - uid ;
 for ( n = 0 , p = uid ;
 n < wlen && s [ n ] != ' ' && s [ n ] ;
 n ++ , p ++ ) {
 if ( word_match_chars [ * p ] != s [ n ] ) break ;
 }
 if ( n == wlen && ( s [ n ] == ' ' || ! s [ n ] ) ) break ;
 uid += wlen ;
 uidlen -= wlen ;
 }
 while ( uidlen ) ;
 if ( ! uidlen ) return - 1 ;
 for ( ;
 * s != ' ' && * s ;
 s ++ ) ;
 if ( * s ) s ++ ;
 }
 return 0 ;
 }