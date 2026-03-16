void globfree ( pglob ) register glob_t * pglob ;
 {
 if ( pglob -> gl_pathv != NULL ) {
 size_t i ;
 for ( i = 0 ;
 i < pglob -> gl_pathc ;
 ++ i ) free ( pglob -> gl_pathv [ pglob -> gl_offs + i ] ) ;
 free ( pglob -> gl_pathv ) ;
 pglob -> gl_pathv = NULL ;
 }
 }