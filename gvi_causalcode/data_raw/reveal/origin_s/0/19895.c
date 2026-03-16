static void dumpspace ( SplineChar * sc , struct glyphinfo * gi ) {
 DBounds b ;
 gi -> pointcounts [ gi -> next_glyph ] = 0 ;
 gi -> loca [ gi -> next_glyph ++ ] = ftell ( gi -> glyphs ) ;
 memset ( & b , 0 , sizeof ( b ) ) ;
 ttfdumpmetrics ( sc , gi , & b ) ;
 }