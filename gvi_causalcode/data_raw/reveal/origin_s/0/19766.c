static void dumpglyph ( SplineChar * sc , struct glyphinfo * gi ) {
 struct glyphhead gh ;
 DBounds bb ;
 SplineSet * ss , * ttfss ;
 int contourcnt , ptcnt , origptcnt ;
 BasePoint * bp ;
 char * fs ;
 SplineChar * isc = sc -> ttf_instrs == NULL && sc -> parent -> mm != NULL && sc -> parent -> mm -> apple ? sc -> parent -> mm -> normal -> glyphs [ sc -> orig_pos ] : sc ;
 if ( sc -> layers [ gi -> layer ] . splines == NULL && sc -> layers [ gi -> layer ] . refs == NULL ) {
 dumpspace ( sc , gi ) ;
 return ;
 }
 if ( gi -> next_glyph != sc -> ttf_glyph ) IError ( "Glyph count wrong in ttf output" ) ;
 if ( gi -> next_glyph >= gi -> maxp -> numGlyphs ) IError ( "max glyph count wrong in ttf output" ) ;
 gi -> loca [ gi -> next_glyph ] = ftell ( gi -> glyphs ) ;
 ttfss = SCttfApprox ( sc , gi -> layer ) ;
 ptcnt = SSTtfNumberPoints ( ttfss ) ;
 for ( ss = ttfss , contourcnt = 0 ;
 ss != NULL ;
 ss = ss -> next ) {
 ++ contourcnt ;
 }
 origptcnt = ptcnt ;
 SplineSetQuickBounds ( ttfss , & bb ) ;
 gh . numContours = contourcnt ;
 gh . xmin = floor ( bb . minx ) ;
 gh . ymin = floor ( bb . miny ) ;
 gh . xmax = ceil ( bb . maxx ) ;
 gh . ymax = ceil ( bb . maxy ) ;
 dumpghstruct ( gi , & gh ) ;
 if ( contourcnt > gi -> maxp -> maxContours ) gi -> maxp -> maxContours = contourcnt ;
 if ( ptcnt > gi -> maxp -> maxPoints ) gi -> maxp -> maxPoints = ptcnt ;
 bp = malloc ( ptcnt * sizeof ( BasePoint ) ) ;
 fs = malloc ( ptcnt ) ;
 ptcnt = contourcnt = 0 ;
 for ( ss = ttfss ;
 ss != NULL ;
 ss = ss -> next ) {
 ptcnt = SSAddPoints ( ss , ptcnt , bp , fs ) ;
 putshort ( gi -> glyphs , ptcnt - 1 ) ;
 }
 if ( ptcnt != origptcnt ) IError ( "Point count wrong calculated=%d, actual=%d in %.20s" , origptcnt , ptcnt , sc -> name ) ;
 gi -> pointcounts [ gi -> next_glyph ++ ] = ptcnt ;
 dumpinstrs ( gi , isc -> ttf_instrs , isc -> ttf_instrs_len ) ;
 dumppointarrays ( gi , bp , fs , ptcnt ) ;
 SplinePointListsFree ( ttfss ) ;
 free ( bp ) ;
 free ( fs ) ;
 ttfdumpmetrics ( sc , gi , & bb ) ;
 }