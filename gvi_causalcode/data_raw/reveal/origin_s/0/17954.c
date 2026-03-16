static void word ( struct vars * v , int dir , struct state * lp , struct state * rp ) {
 assert ( dir == AHEAD || dir == BEHIND ) ;
 cloneouts ( v -> nfa , v -> wordchrs , lp , rp , dir ) ;
 }