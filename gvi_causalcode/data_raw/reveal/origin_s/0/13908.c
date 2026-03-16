static void ECCategorizePoints ( EntityChar * ec ) {
 Entity * ent ;
 for ( ent = ec -> splines ;
 ent != NULL ;
 ent = ent -> next ) if ( ent -> type == et_splines ) {
 SPLCategorizePoints ( ent -> u . splines . splines ) ;
 SPLCategorizePoints ( ent -> clippath ) ;
 }
 }