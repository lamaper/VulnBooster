static int dumpnoglyphs ( struct glyphinfo * gi ) {
 gi -> glyphs = tmpfile ( ) ;
 gi -> glyph_len = 0 ;
 return ( true ) ;
 }