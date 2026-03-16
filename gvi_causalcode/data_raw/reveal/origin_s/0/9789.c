static void nonword ( struct vars * v , int dir , struct state * lp , struct state * rp ) {
 int anchor = ( dir == AHEAD ) ? '$' : '^' ;
 assert ( dir == AHEAD || dir == BEHIND ) ;
 newarc ( v -> nfa , anchor , 1 , lp , rp ) ;
 newarc ( v -> nfa , anchor , 0 , lp , rp ) ;
 colorcomplement ( v -> nfa , v -> cm , dir , v -> wordchrs , lp , rp ) ;
 }