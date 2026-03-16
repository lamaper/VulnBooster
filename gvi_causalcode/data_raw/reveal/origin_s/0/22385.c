static void bracket ( struct vars * v , struct state * lp , struct state * rp ) {
 assert ( SEE ( '[' ) ) ;
 NEXT ( ) ;
 while ( ! SEE ( ']' ) && ! SEE ( EOS ) ) brackpart ( v , lp , rp ) ;
 assert ( SEE ( ']' ) || ISERR ( ) ) ;
 okcolors ( v -> nfa , v -> cm ) ;
 }