static void onechr ( struct vars * v , chr c , struct state * lp , struct state * rp ) {
 if ( ! ( v -> cflags & REG_ICASE ) ) {
 newarc ( v -> nfa , PLAIN , subcolor ( v -> cm , c ) , lp , rp ) ;
 return ;
 }
 dovec ( v , allcases ( v , c ) , lp , rp ) ;
 }