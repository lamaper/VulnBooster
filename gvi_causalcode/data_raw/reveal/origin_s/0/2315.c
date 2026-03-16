static void dumpblankglyph ( struct glyphinfo * gi , SplineFont * sf , int fixedwidth ) {
 int advance = gi -> next_glyph == 1 ? 0 : fixedwidth <= 0 ? ( sf -> ascent + sf -> descent ) / 3 : fixedwidth ;
 gi -> pointcounts [ gi -> next_glyph ] = 0 ;
 gi -> loca [ gi -> next_glyph ++ ] = ftell ( gi -> glyphs ) ;
 putshort ( gi -> hmtx , advance ) ;
 putshort ( gi -> hmtx , 0 ) ;
 if ( sf -> hasvmetrics ) {
 putshort ( gi -> vmtx , gi -> next_glyph == 2 ? 0 : ( sf -> ascent + sf -> descent ) ) ;
 putshort ( gi -> vmtx , 0 ) ;
 }
 }