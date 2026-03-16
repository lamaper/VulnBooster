static void markst ( struct subre * t ) {
 assert ( t != NULL ) ;
 t -> flags |= INUSE ;
 if ( t -> left != NULL ) markst ( t -> left ) ;
 if ( t -> right != NULL ) markst ( t -> right ) ;
 }