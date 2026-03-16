static chr chrnamed ( struct vars * v , const chr * startp , const chr * endp , chr lastresort ) {
 celt c ;
 int errsave ;
 int e ;
 struct cvec * cv ;
 errsave = v -> err ;
 v -> err = 0 ;
 c = element ( v , startp , endp ) ;
 e = v -> err ;
 v -> err = errsave ;
 if ( e != 0 ) return ( chr ) lastresort ;
 cv = range ( v , c , c , 0 ) ;
 if ( cv -> nchrs == 0 ) return ( chr ) lastresort ;
 return cv -> chrs [ 0 ] ;
 }