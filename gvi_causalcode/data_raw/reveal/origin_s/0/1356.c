static void RefigureCompositeMaxPts ( SplineFont * sf , struct glyphinfo * gi ) {
 int i ;
 for ( i = 0 ;
 i < gi -> gcnt ;
 ++ i ) if ( gi -> bygid [ i ] != - 1 && sf -> glyphs [ gi -> bygid [ i ] ] -> ttf_glyph != - 1 ) {
 if ( sf -> glyphs [ gi -> bygid [ i ] ] -> layers [ gi -> layer ] . splines == NULL && sf -> glyphs [ gi -> bygid [ i ] ] -> layers [ gi -> layer ] . refs != NULL && gi -> pointcounts [ i ] == - 1 ) CountCompositeMaxPts ( sf -> glyphs [ gi -> bygid [ i ] ] , gi ) ;
 }
 }