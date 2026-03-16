void SFSetLayerWidthsStroked ( SplineFont * sf , real strokewidth ) {
 int i ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 SplineChar * sc = sf -> glyphs [ i ] ;
 sc -> layers [ ly_fore ] . dofill = false ;
 sc -> layers [ ly_fore ] . dostroke = true ;
 sc -> layers [ ly_fore ] . stroke_pen . width = strokewidth ;
 }
 }