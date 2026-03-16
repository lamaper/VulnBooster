static void wordchrs ( struct vars * v ) {
 struct state * left ;
 struct state * right ;
 if ( v -> wordchrs != NULL ) {
 NEXT ( ) ;
 return ;
 }
 left = newstate ( v -> nfa ) ;
 right = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 lexword ( v ) ;
 NEXT ( ) ;
 assert ( v -> savenow != NULL && SEE ( '[' ) ) ;
 bracket ( v , left , right ) ;
 assert ( ( v -> savenow != NULL && SEE ( ']' ) ) || ISERR ( ) ) ;
 NEXT ( ) ;
 NOERR ( ) ;
 v -> wordchrs = left ;
 }