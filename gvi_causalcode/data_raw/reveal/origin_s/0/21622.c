static int numst ( struct subre * t , int start ) {
 int i ;
 assert ( t != NULL ) ;
 i = start ;
 t -> id = ( short ) i ++ ;
 if ( t -> left != NULL ) i = numst ( t -> left , i ) ;
 if ( t -> right != NULL ) i = numst ( t -> right , i ) ;
 return i ;
 }