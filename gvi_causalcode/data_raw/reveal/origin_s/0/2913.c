static void ttfdumpmetrics ( SplineChar * sc , struct glyphinfo * gi , DBounds * b ) {
 int width = sc -> width ;
 int vwidth = sc -> vwidth ;
 if ( width < 0 ) width = 0 ;
 if ( vwidth < 0 ) vwidth = 0 ;
 if ( sc -> ttf_glyph <= gi -> lasthwidth ) putshort ( gi -> hmtx , width ) ;
 putshort ( gi -> hmtx , b -> minx ) ;
 if ( sc -> parent -> hasvmetrics ) {
 if ( sc -> ttf_glyph <= gi -> lastvwidth ) putshort ( gi -> vmtx , vwidth ) ;
 putshort ( gi -> vmtx , sc -> parent -> ascent - b -> maxy ) ;
 }
 if ( sc -> ttf_glyph == gi -> lasthwidth ) gi -> hfullcnt = sc -> ttf_glyph + 1 ;
 if ( sc -> ttf_glyph == gi -> lastvwidth ) gi -> vfullcnt = sc -> ttf_glyph + 1 ;
 }