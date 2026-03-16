static struct cvec * range ( struct vars * v , celt a , celt b , int cases ) {
 int nchrs ;
 struct cvec * cv ;
 celt c , cc ;
 if ( a != b && ! before ( a , b ) ) {
 ERR ( REG_ERANGE ) ;
 return NULL ;
 }
 if ( ! cases ) {
 cv = getcvec ( v , 0 , 1 ) ;
 NOERRN ( ) ;
 addrange ( cv , a , b ) ;
 return cv ;
 }
 nchrs = b - a + 1 ;
 if ( nchrs <= 0 || nchrs > 100000 ) nchrs = 100000 ;
 cv = getcvec ( v , nchrs , 1 ) ;
 NOERRN ( ) ;
 addrange ( cv , a , b ) ;
 for ( c = a ;
 c <= b ;
 c ++ ) {
 cc = pg_wc_tolower ( ( chr ) c ) ;
 if ( cc != c && ( before ( cc , a ) || before ( b , cc ) ) ) {
 if ( cv -> nchrs >= cv -> chrspace ) {
 ERR ( REG_ETOOBIG ) ;
 return NULL ;
 }
 addchr ( cv , cc ) ;
 }
 cc = pg_wc_toupper ( ( chr ) c ) ;
 if ( cc != c && ( before ( cc , a ) || before ( b , cc ) ) ) {
 if ( cv -> nchrs >= cv -> chrspace ) {
 ERR ( REG_ETOOBIG ) ;
 return NULL ;
 }
 addchr ( cv , cc ) ;
 }
 if ( CANCEL_REQUESTED ( v -> re ) ) {
 ERR ( REG_CANCEL ) ;
 return NULL ;
 }
 }
 return cv ;
 }