static void rfree ( regex_t * re ) {
 struct guts * g ;
 if ( re == NULL || re -> re_magic != REMAGIC ) return ;
 re -> re_magic = 0 ;
 g = ( struct guts * ) re -> re_guts ;
 re -> re_guts = NULL ;
 re -> re_fns = NULL ;
 if ( g != NULL ) {
 g -> magic = 0 ;
 freecm ( & g -> cmap ) ;
 if ( g -> tree != NULL ) freesubre ( ( struct vars * ) NULL , g -> tree ) ;
 if ( g -> lacons != NULL ) freelacons ( g -> lacons , g -> nlacons ) ;
 if ( ! NULLCNFA ( g -> search ) ) freecnfa ( & g -> search ) ;
 FREE ( g ) ;
 }
 }