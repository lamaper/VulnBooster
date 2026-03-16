static int compare_name ( int mode , const char * name , const char * uid , size_t uidlen ) {
 int i ;
 const char * s , * se ;
 if ( mode == KEYDB_SEARCH_MODE_EXACT ) {
 for ( i = 0 ;
 name [ i ] && uidlen ;
 i ++ , uidlen -- ) if ( uid [ i ] != name [ i ] ) break ;
 if ( ! uidlen && ! name [ i ] ) return 0 ;
 }
 else if ( mode == KEYDB_SEARCH_MODE_SUBSTR ) {
 if ( ascii_memistr ( uid , uidlen , name ) ) return 0 ;
 }
 else if ( mode == KEYDB_SEARCH_MODE_MAIL || mode == KEYDB_SEARCH_MODE_MAILSUB || mode == KEYDB_SEARCH_MODE_MAILEND ) {
 for ( i = 0 , s = uid ;
 i < uidlen && * s != '<' ;
 s ++ , i ++ ) ;
 if ( i < uidlen ) {
 s ++ ;
 i ++ ;
 for ( se = s + 1 , i ++ ;
 i < uidlen && * se != '>' ;
 se ++ , i ++ ) ;
 if ( i < uidlen ) {
 i = se - s ;
 if ( mode == KEYDB_SEARCH_MODE_MAIL ) {
 if ( strlen ( name ) - 2 == i && ! ascii_memcasecmp ( s , name + 1 , i ) ) return 0 ;
 }
 else if ( mode == KEYDB_SEARCH_MODE_MAILSUB ) {
 if ( ascii_memistr ( s , i , name ) ) return 0 ;
 }
 else {
 }
 }
 }
 }
 else if ( mode == KEYDB_SEARCH_MODE_WORDS ) return word_match ( uid , uidlen , name ) ;
 else BUG ( ) ;
 return - 1 ;
 }