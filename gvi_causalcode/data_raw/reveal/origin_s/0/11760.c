static struct subre * parse ( struct vars * v , int stopper , int type , struct state * init , struct state * final ) {
 struct state * left ;
 struct state * right ;
 struct subre * branches ;
 struct subre * branch ;
 struct subre * t ;
 int firstbranch ;
 assert ( stopper == ')' || stopper == EOS ) ;
 branches = subre ( v , '|' , LONGER , init , final ) ;
 NOERRN ( ) ;
 branch = branches ;
 firstbranch = 1 ;
 do {
 if ( ! firstbranch ) {
 branch -> right = subre ( v , '|' , LONGER , init , final ) ;
 NOERRN ( ) ;
 branch = branch -> right ;
 }
 firstbranch = 0 ;
 left = newstate ( v -> nfa ) ;
 right = newstate ( v -> nfa ) ;
 NOERRN ( ) ;
 EMPTYARC ( init , left ) ;
 EMPTYARC ( right , final ) ;
 NOERRN ( ) ;
 branch -> left = parsebranch ( v , stopper , type , left , right , 0 ) ;
 NOERRN ( ) ;
 branch -> flags |= UP ( branch -> flags | branch -> left -> flags ) ;
 if ( ( branch -> flags & ~ branches -> flags ) != 0 ) for ( t = branches ;
 t != branch ;
 t = t -> right ) t -> flags |= branch -> flags ;
 }
 while ( EAT ( '|' ) ) ;
 assert ( SEE ( stopper ) || SEE ( EOS ) ) ;
 if ( ! SEE ( stopper ) ) {
 assert ( stopper == ')' && SEE ( EOS ) ) ;
 ERR ( REG_EPAREN ) ;
 }
 if ( branch == branches ) {
 assert ( branch -> right == NULL ) ;
 t = branch -> left ;
 branch -> left = NULL ;
 freesubre ( v , branches ) ;
 branches = t ;
 }
 else if ( ! MESSY ( branches -> flags ) ) {
 freesubre ( v , branches -> left ) ;
 branches -> left = NULL ;
 freesubre ( v , branches -> right ) ;
 branches -> right = NULL ;
 branches -> op = '=' ;
 }
 return branches ;
 }