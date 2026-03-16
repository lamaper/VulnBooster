static long nfatree ( struct vars * v , struct subre * t , FILE * f ) {
 assert ( t != NULL && t -> begin != NULL ) ;
 if ( t -> left != NULL ) ( DISCARD ) nfatree ( v , t -> left , f ) ;
 if ( t -> right != NULL ) ( DISCARD ) nfatree ( v , t -> right , f ) ;
 return nfanode ( v , t , 0 , f ) ;
 }