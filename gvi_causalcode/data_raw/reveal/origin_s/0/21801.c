static int dumpglyphs ( SplineFont * sf , struct glyphinfo * gi ) {
 int i ;
 int fixed = gi -> fixed_width ;
 int answer , answered = - 1 ;
 ff_progress_change_stages ( 2 + gi -> strikecnt ) ;
 QuickBlues ( sf , gi -> layer , & gi -> bd ) ;
 ff_progress_next_stage ( ) ;
 if ( ! gi -> onlybitmaps ) {
 if ( sf -> layers [ gi -> layer ] . order2 ) for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) {
 SplineChar * sc = sf -> glyphs [ i ] ;
 if ( SCWorthOutputting ( sc ) ) if ( ! SCPointsNumberedProperly ( sc , gi -> layer ) ) {
 if ( answered == - 1 && sc -> ttf_instrs_len != 0 ) {
 char * buts [ 5 ] ;
 buts [ 0 ] = _ ( "_Yes" ) ;
 buts [ 1 ] = _ ( "Yes to _All" ) ;
 buts [ 2 ] = _ ( "No _to All" ) ;
 buts [ 3 ] = _ ( "_No" ) ;
 buts [ 4 ] = NULL ;
 ff_progress_pause_timer ( ) ;
 answer = ff_ask ( _ ( "Bad Point Numbering" ) , ( const char * * ) buts , 0 , 3 , _ ( "The points in %s are not numbered properly. This means that any instructions will probably move the wrong points and do the wrong thing.\nWould you like me to remove the instructions?" ) , sc -> name ) ;
 if ( answer == 1 || answer == 2 ) answered = answer ;
 }
 else answer = answered ;
 if ( answer == 0 ) {
 free ( sc -> ttf_instrs ) ;
 sc -> ttf_instrs = NULL ;
 sc -> ttf_instrs_len = 0 ;
 SCMarkInstrDlgAsChanged ( sc ) ;
 }
 SCNumberPoints ( sc , gi -> layer ) ;
 }
 }
 }
 gi -> maxp -> numGlyphs = gi -> gcnt ;
 gi -> loca = malloc ( ( gi -> maxp -> numGlyphs + 1 ) * sizeof ( uint32 ) ) ;
 gi -> pointcounts = malloc ( ( gi -> maxp -> numGlyphs + 1 ) * sizeof ( int32 ) ) ;
 memset ( gi -> pointcounts , - 1 , ( gi -> maxp -> numGlyphs + 1 ) * sizeof ( int32 ) ) ;
 gi -> next_glyph = 0 ;
 gi -> glyphs = tmpfile ( ) ;
 gi -> hmtx = tmpfile ( ) ;
 if ( sf -> hasvmetrics ) gi -> vmtx = tmpfile ( ) ;
 FigureFullMetricsEnd ( sf , gi , true ) ;
 if ( fixed > 0 ) {
 gi -> lasthwidth = 3 ;
 gi -> hfullcnt = 3 ;
 }
 for ( i = 0 ;
 i < gi -> gcnt ;
 ++ i ) {
 if ( i == 0 ) {
 if ( gi -> bygid [ 0 ] != - 1 && ( fixed <= 0 || sf -> glyphs [ gi -> bygid [ 0 ] ] -> width == fixed ) ) dumpglyph ( sf -> glyphs [ gi -> bygid [ 0 ] ] , gi ) ;
 else dumpmissingglyph ( sf , gi , fixed ) ;
 }
 else if ( i <= 2 && gi -> bygid [ i ] == - 1 ) dumpblankglyph ( gi , sf , fixed ) ;
 else if ( gi -> onlybitmaps ) {
 if ( gi -> bygid [ i ] != - 1 && sf -> glyphs [ gi -> bygid [ i ] ] -> ttf_glyph > 0 ) dumpspace ( sf -> glyphs [ gi -> bygid [ i ] ] , gi ) ;
 }
 else {
 if ( gi -> bygid [ i ] != - 1 && sf -> glyphs [ gi -> bygid [ i ] ] -> ttf_glyph > 0 ) {
 if ( IsTTFRefable ( sf -> glyphs [ gi -> bygid [ i ] ] , gi -> layer ) ) dumpcomposite ( sf -> glyphs [ gi -> bygid [ i ] ] , gi ) ;
 else dumpglyph ( sf -> glyphs [ gi -> bygid [ i ] ] , gi ) ;
 }
 }
 if ( ( ftell ( gi -> glyphs ) & 3 ) != 0 ) {
 if ( ftell ( gi -> glyphs ) & 1 ) putc ( '\0' , gi -> glyphs ) ;
 if ( ftell ( gi -> glyphs ) & 2 ) putshort ( gi -> glyphs , 0 ) ;
 }
 if ( ! ff_progress_next ( ) ) return ( false ) ;
 }
 gi -> loca [ gi -> next_glyph ] = ftell ( gi -> glyphs ) ;
 gi -> glyph_len = ftell ( gi -> glyphs ) ;
 gi -> hmtxlen = ftell ( gi -> hmtx ) ;
 if ( gi -> hmtxlen & 2 ) putshort ( gi -> hmtx , 0 ) ;
 if ( gi -> loca [ gi -> next_glyph ] & 3 ) {
 for ( i = 4 - ( gi -> loca [ gi -> next_glyph ] & 3 ) ;
 i > 0 ;
 -- i ) putc ( '\0' , gi -> glyphs ) ;
 }
 if ( sf -> hasvmetrics ) {
 gi -> vmtxlen = ftell ( gi -> vmtx ) ;
 if ( gi -> vmtxlen & 2 ) putshort ( gi -> vmtx , 0 ) ;
 }
 if ( ! sf -> layers [ gi -> layer ] . order2 ) RefigureCompositeMaxPts ( sf , gi ) ;
 free ( gi -> pointcounts ) ;
 return ( true ) ;
 }