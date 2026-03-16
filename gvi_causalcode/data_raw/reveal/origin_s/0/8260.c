static struct subre * subre ( struct vars * v , int op , int flags , struct state * begin , struct state * end ) {
 struct subre * ret = v -> treefree ;
 if ( STACK_TOO_DEEP ( v -> re ) ) {
 ERR ( REG_ETOOBIG ) ;
 return NULL ;
 }
 if ( ret != NULL ) v -> treefree = ret -> left ;
 else {
 ret = ( struct subre * ) MALLOC ( sizeof ( struct subre ) ) ;
 if ( ret == NULL ) {
 ERR ( REG_ESPACE ) ;
 return NULL ;
 }
 ret -> chain = v -> treechain ;
 v -> treechain = ret ;
 }
 assert ( strchr ( "=b|.*(" , op ) != NULL ) ;
 ret -> op = op ;
 ret -> flags = flags ;
 ret -> id = 0 ;
 ret -> subno = 0 ;
 ret -> min = ret -> max = 1 ;
 ret -> left = NULL ;
 ret -> right = NULL ;
 ret -> begin = begin ;
 ret -> end = end ;
 ZAPCNFA ( ret -> cnfa ) ;
 return ret ;
 }