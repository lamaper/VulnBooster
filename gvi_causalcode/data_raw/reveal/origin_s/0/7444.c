static void cbracket ( struct vars * v , struct state * lp , struct state * rp ) {
 struct state * left = newstate ( v -> nfa ) ;
 struct state * right = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 bracket ( v , left , right ) ;
 if ( v -> cflags & REG_NLSTOP ) newarc ( v -> nfa , PLAIN , v -> nlcolor , left , right ) ;
 NOERR ( ) ;
 assert ( lp -> nouts == 0 ) ;
 colorcomplement ( v -> nfa , v -> cm , PLAIN , left , lp , rp ) ;
 NOERR ( ) ;
 dropstate ( v -> nfa , left ) ;
 assert ( right -> nins == 0 ) ;
 freestate ( v -> nfa , right ) ;
 }