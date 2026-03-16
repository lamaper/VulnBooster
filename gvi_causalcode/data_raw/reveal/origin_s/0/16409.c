static void makesearch ( struct vars * v , struct nfa * nfa ) {
 struct arc * a ;
 struct arc * b ;
 struct state * pre = nfa -> pre ;
 struct state * s ;
 struct state * s2 ;
 struct state * slist ;
 for ( a = pre -> outs ;
 a != NULL ;
 a = a -> outchain ) {
 assert ( a -> type == PLAIN ) ;
 if ( a -> co != nfa -> bos [ 0 ] && a -> co != nfa -> bos [ 1 ] ) break ;
 }
 if ( a != NULL ) {
 rainbow ( nfa , v -> cm , PLAIN , COLORLESS , pre , pre ) ;
 newarc ( nfa , PLAIN , nfa -> bos [ 0 ] , pre , pre ) ;
 newarc ( nfa , PLAIN , nfa -> bos [ 1 ] , pre , pre ) ;
 }
 slist = NULL ;
 for ( a = pre -> outs ;
 a != NULL ;
 a = a -> outchain ) {
 s = a -> to ;
 for ( b = s -> ins ;
 b != NULL ;
 b = b -> inchain ) {
 if ( b -> from != pre ) break ;
 }
 if ( b != NULL && s -> tmp == NULL ) {
 s -> tmp = ( slist != NULL ) ? slist : s ;
 slist = s ;
 }
 }
 for ( s = slist ;
 s != NULL ;
 s = s2 ) {
 s2 = newstate ( nfa ) ;
 NOERR ( ) ;
 copyouts ( nfa , s , s2 ) ;
 NOERR ( ) ;
 for ( a = s -> ins ;
 a != NULL ;
 a = b ) {
 b = a -> inchain ;
 if ( a -> from != pre ) {
 cparc ( nfa , a , a -> from , s2 ) ;
 freearc ( nfa , a ) ;
 }
 }
 s2 = ( s -> tmp != s ) ? s -> tmp : NULL ;
 s -> tmp = NULL ;
 }
 }