static void freesrnode ( struct vars * v , struct subre * sr ) {
 if ( sr == NULL ) return ;
 if ( ! NULLCNFA ( sr -> cnfa ) ) freecnfa ( & sr -> cnfa ) ;
 sr -> flags = 0 ;
 if ( v != NULL && v -> treechain != NULL ) {
 sr -> left = v -> treefree ;
 v -> treefree = sr ;
 }
 else FREE ( sr ) ;
 }