static void freesubre ( struct vars * v , struct subre * sr ) {
 if ( sr == NULL ) return ;
 if ( sr -> left != NULL ) freesubre ( v , sr -> left ) ;
 if ( sr -> right != NULL ) freesubre ( v , sr -> right ) ;
 freesrnode ( v , sr ) ;
 }