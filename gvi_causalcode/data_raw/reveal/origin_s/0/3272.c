static long nfanode ( struct vars * v , struct subre * t , int converttosearch , FILE * f ) {
 struct nfa * nfa ;
 long ret = 0 ;
 assert ( t -> begin != NULL ) ;

 char idbuf [ 50 ] ;
 fprintf ( f , "\n\n\n========= TREE NODE %s ==========\n" , stid ( t , idbuf , sizeof ( idbuf ) ) ) ;
 }

 NOERRZ ( ) ;
 dupnfa ( nfa , t -> begin , t -> end , nfa -> init , nfa -> final ) ;
 if ( ! ISERR ( ) ) specialcolors ( nfa ) ;
 if ( ! ISERR ( ) ) ret = optimize ( nfa , f ) ;
 if ( converttosearch && ! ISERR ( ) ) makesearch ( v , nfa ) ;
 if ( ! ISERR ( ) ) compact ( nfa , & t -> cnfa ) ;
 freenfa ( nfa ) ;
 return ret ;
 }