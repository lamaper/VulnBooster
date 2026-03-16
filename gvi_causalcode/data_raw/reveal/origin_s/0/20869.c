static struct subre * parsebranch ( struct vars * v , int stopper , int type , struct state * left , struct state * right , int partial ) {
 struct state * lp ;
 int seencontent ;
 struct subre * t ;
 lp = left ;
 seencontent = 0 ;
 t = subre ( v , '=' , 0 , left , right ) ;
 NOERRN ( ) ;
 while ( ! SEE ( '|' ) && ! SEE ( stopper ) && ! SEE ( EOS ) ) {
 if ( seencontent ) {
 lp = newstate ( v -> nfa ) ;
 NOERRN ( ) ;
 moveins ( v -> nfa , right , lp ) ;
 }
 seencontent = 1 ;
 parseqatom ( v , stopper , type , lp , right , t ) ;
 NOERRN ( ) ;
 }
 if ( ! seencontent ) {
 if ( ! partial ) NOTE ( REG_UUNSPEC ) ;
 assert ( lp == left ) ;
 EMPTYARC ( left , right ) ;
 }
 return t ;
 }