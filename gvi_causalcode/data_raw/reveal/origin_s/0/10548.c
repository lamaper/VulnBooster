static void cleanst ( struct vars * v ) {
 struct subre * t ;
 struct subre * next ;
 for ( t = v -> treechain ;
 t != NULL ;
 t = next ) {
 next = t -> chain ;
 if ( ! ( t -> flags & INUSE ) ) FREE ( t ) ;
 }
 v -> treechain = NULL ;
 v -> treefree = NULL ;
 }