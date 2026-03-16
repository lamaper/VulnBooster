void pkg_deleteList ( CharList * l ) {
 CharList * tmp ;
 while ( l != NULL ) {
 uprv_free ( ( void * ) l -> str ) ;
 tmp = l ;
 l = l -> next ;
 uprv_free ( tmp ) ;
 }
 }