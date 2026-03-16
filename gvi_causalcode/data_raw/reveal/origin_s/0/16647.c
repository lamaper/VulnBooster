static void EntityCharCorrectDir ( EntityChar * ec ) {
 SplineSet * ss ;
 Entity * ent ;
 int changed ;
 for ( ent = ec -> splines ;
 ent != NULL ;
 ent = ent -> next ) {
 if ( ent -> type == et_splines && ent -> u . splines . fill . col != 0xffffffff ) {
 SplineSetsCorrect ( ent -> u . splines . splines , & changed ) ;
 if ( ent -> u . splines . fill . col == 0xffffff ) {
 for ( ss = ent -> u . splines . splines ;
 ss != NULL ;
 ss = ss -> next ) SplineSetReverse ( ss ) ;
 }
 SplineSetsCorrect ( ent -> clippath , & changed ) ;
 }
 }
 }