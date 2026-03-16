static struct cvec * allcases ( struct vars * v , chr pc ) {
 struct cvec * cv ;
 chr c = ( chr ) pc ;
 chr lc , uc ;
 lc = pg_wc_tolower ( ( chr ) c ) ;
 uc = pg_wc_toupper ( ( chr ) c ) ;
 cv = getcvec ( v , 2 , 0 ) ;
 addchr ( cv , lc ) ;
 if ( lc != uc ) addchr ( cv , uc ) ;
 return cv ;
 }