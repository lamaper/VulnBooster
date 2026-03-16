static void CountCompositeMaxPts ( SplineChar * sc , struct glyphinfo * gi ) {
 RefChar * ref ;
 int ptcnt = 0 , index ;
 for ( ref = sc -> layers [ gi -> layer ] . refs ;
 ref != NULL ;
 ref = ref -> next ) {
 if ( ref -> sc -> ttf_glyph == - 1 ) continue ;
 index = ref -> sc -> ttf_glyph ;
 if ( gi -> pointcounts [ index ] == - 1 ) CountCompositeMaxPts ( ref -> sc , gi ) ;
 ptcnt += gi -> pointcounts [ index ] ;
 }
 gi -> pointcounts [ sc -> ttf_glyph ] = ptcnt ;
 if ( gi -> maxp -> maxCompositPts < ptcnt ) gi -> maxp -> maxCompositPts = ptcnt ;
 }