static void closepath ( SplinePointList * cur , int is_type2 ) {
 if ( cur != NULL && cur -> first == cur -> last && cur -> first -> prev == NULL && is_type2 ) return ;
 if ( cur != NULL && cur -> first != NULL && cur -> first != cur -> last ) {
 if ( RealWithin ( cur -> first -> me . x , cur -> last -> me . x , .05 ) && RealWithin ( cur -> first -> me . y , cur -> last -> me . y , .05 ) ) {
 SplinePoint * oldlast = cur -> last ;
 cur -> first -> prevcp = oldlast -> prevcp ;
 cur -> first -> prevcp . x += ( cur -> first -> me . x - oldlast -> me . x ) ;
 cur -> first -> prevcp . y += ( cur -> first -> me . y - oldlast -> me . y ) ;
 cur -> first -> noprevcp = oldlast -> noprevcp ;
 oldlast -> prev -> from -> next = NULL ;
 cur -> last = oldlast -> prev -> from ;
 chunkfree ( oldlast -> prev , sizeof ( * oldlast ) ) ;
 chunkfree ( oldlast -> hintmask , sizeof ( HintMask ) ) ;
 chunkfree ( oldlast , sizeof ( * oldlast ) ) ;
 }
 CheckMake ( cur -> last , cur -> first ) ;
 SplineMake3 ( cur -> last , cur -> first ) ;
 cur -> last = cur -> first ;
 }
 }