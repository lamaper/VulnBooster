static void dumpcomposite ( SplineChar * sc , struct glyphinfo * gi ) {
 struct glyphhead gh ;
 DBounds bb ;
 int i , ptcnt , ctcnt , flags , sptcnt , rd ;
 SplineSet * ss ;
 RefChar * ref ;
 SplineChar * isc = sc -> ttf_instrs == NULL && sc -> parent -> mm != NULL && sc -> parent -> mm -> apple ? sc -> parent -> mm -> normal -> glyphs [ sc -> orig_pos ] : sc ;
 int arg1 , arg2 ;
 if ( gi -> next_glyph != sc -> ttf_glyph ) IError ( "Glyph count wrong in ttf output" ) ;
 if ( gi -> next_glyph >= gi -> maxp -> numGlyphs ) IError ( "max glyph count wrong in ttf output" ) ;
 gi -> loca [ gi -> next_glyph ] = ftell ( gi -> glyphs ) ;
 SplineCharLayerQuickBounds ( sc , gi -> layer , & bb ) ;
 gh . numContours = - 1 ;
 gh . xmin = floor ( bb . minx ) ;
 gh . ymin = floor ( bb . miny ) ;
 gh . xmax = ceil ( bb . maxx ) ;
 gh . ymax = ceil ( bb . maxy ) ;
 dumpghstruct ( gi , & gh ) ;
 i = ptcnt = ctcnt = 0 ;
 for ( ref = sc -> layers [ gi -> layer ] . refs ;
 ref != NULL ;
 ref = ref -> next , ++ i ) {
 if ( ref -> sc -> ttf_glyph == - 1 ) {
 continue ;
 }
 flags = 0 ;
 if ( ref -> round_translation_to_grid ) flags |= _ROUND ;
 if ( ref -> use_my_metrics ) flags |= _USE_MY_METRICS ;
 if ( ref -> next != NULL ) flags |= _MORE ;
 else if ( isc -> ttf_instrs_len != 0 ) flags |= _INSTR ;
 if ( ref -> transform [ 1 ] != 0 || ref -> transform [ 2 ] != 0 ) flags |= _MATRIX ;
 else if ( ref -> transform [ 0 ] != ref -> transform [ 3 ] ) flags |= _XY_SCALE ;
 else if ( ref -> transform [ 0 ] != 1. ) flags |= _SCALE ;
 if ( ref -> point_match ) {
 arg1 = ref -> match_pt_base ;
 arg2 = ref -> match_pt_ref ;
 }
 else {
 arg1 = rint ( ref -> transform [ 4 ] ) ;
 arg2 = rint ( ref -> transform [ 5 ] ) ;
 flags |= _ARGS_ARE_XY | _UNSCALED_OFFSETS ;
 }
 if ( arg1 < - 128 || arg1 > 127 || arg2 < - 128 || arg2 > 127 ) flags |= _ARGS_ARE_WORDS ;
 putshort ( gi -> glyphs , flags ) ;
 putshort ( gi -> glyphs , ref -> sc -> ttf_glyph == - 1 ? 0 : ref -> sc -> ttf_glyph ) ;
 if ( flags & _ARGS_ARE_WORDS ) {
 putshort ( gi -> glyphs , ( short ) arg1 ) ;
 putshort ( gi -> glyphs , ( short ) arg2 ) ;
 }
 else {
 putc ( ( char ) arg1 , gi -> glyphs ) ;
 putc ( ( char ) arg2 , gi -> glyphs ) ;
 }
 if ( flags & _MATRIX ) {
 put2d14 ( gi -> glyphs , ref -> transform [ 0 ] ) ;
 put2d14 ( gi -> glyphs , ref -> transform [ 1 ] ) ;
 put2d14 ( gi -> glyphs , ref -> transform [ 2 ] ) ;
 put2d14 ( gi -> glyphs , ref -> transform [ 3 ] ) ;
 }
 else if ( flags & _XY_SCALE ) {
 put2d14 ( gi -> glyphs , ref -> transform [ 0 ] ) ;
 put2d14 ( gi -> glyphs , ref -> transform [ 3 ] ) ;
 }
 else if ( flags & _SCALE ) {
 put2d14 ( gi -> glyphs , ref -> transform [ 0 ] ) ;
 }
 sptcnt = SSTtfNumberPoints ( ref -> layers [ 0 ] . splines ) ;
 for ( ss = ref -> layers [ 0 ] . splines ;
 ss != NULL ;
 ss = ss -> next ) {
 ++ ctcnt ;
 }
 if ( sc -> layers [ gi -> layer ] . order2 ) ptcnt += sptcnt ;
 else if ( ptcnt >= 0 && gi -> pointcounts [ ref -> sc -> ttf_glyph == - 1 ? 0 : ref -> sc -> ttf_glyph ] >= 0 ) ptcnt += gi -> pointcounts [ ref -> sc -> ttf_glyph == - 1 ? 0 : ref -> sc -> ttf_glyph ] ;
 else ptcnt = - 1 ;
 rd = RefDepth ( ref , gi -> layer ) ;
 if ( rd > gi -> maxp -> maxcomponentdepth ) gi -> maxp -> maxcomponentdepth = rd ;
 }
 if ( isc -> ttf_instrs_len != 0 ) dumpinstrs ( gi , isc -> ttf_instrs , isc -> ttf_instrs_len ) ;
 gi -> pointcounts [ gi -> next_glyph ++ ] = ptcnt ;
 if ( gi -> maxp -> maxnumcomponents < i ) gi -> maxp -> maxnumcomponents = i ;
 if ( gi -> maxp -> maxCompositPts < ptcnt ) gi -> maxp -> maxCompositPts = ptcnt ;
 if ( gi -> maxp -> maxCompositCtrs < ctcnt ) gi -> maxp -> maxCompositCtrs = ctcnt ;
 ttfdumpmetrics ( sc , gi , & bb ) ;
 if ( ftell ( gi -> glyphs ) & 1 ) putc ( '\0' , gi -> glyphs ) ;
 }