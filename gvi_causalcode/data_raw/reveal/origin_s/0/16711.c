static struct cvec * eclass ( struct vars * v , celt c , int cases ) {
 struct cvec * cv ;
 if ( ( v -> cflags & REG_FAKE ) && c == 'x' ) {
 cv = getcvec ( v , 4 , 0 ) ;
 addchr ( cv , ( chr ) 'x' ) ;
 addchr ( cv , ( chr ) 'y' ) ;
 if ( cases ) {
 addchr ( cv , ( chr ) 'X' ) ;
 addchr ( cv , ( chr ) 'Y' ) ;
 }
 return cv ;
 }
 if ( cases ) return allcases ( v , c ) ;
 cv = getcvec ( v , 1 , 0 ) ;
 assert ( cv != NULL ) ;
 addchr ( cv , ( chr ) c ) ;
 return cv ;
 }