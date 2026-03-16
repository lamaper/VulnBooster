static int AssignTTFGlyph ( struct glyphinfo * gi , SplineFont * sf , EncMap * map , int iscff ) {
 int * bygid = malloc ( ( sf -> glyphcnt + 3 ) * sizeof ( int ) ) ;
 int i , j ;
 memset ( bygid , 0xff , ( sf -> glyphcnt + 3 ) * sizeof ( int ) ) ;
 AssignNotdefNull ( sf , bygid , iscff ) ;
 j = iscff ? 1 : 3 ;
 for ( i = 0 ;
 i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 ) {
 SplineChar * sc = sf -> glyphs [ map -> map [ i ] ] ;
 if ( SCWorthOutputting ( sc ) && sc -> ttf_glyph == - 1 # if HANYANG && ( ! iscff || ! sc -> compositionunit ) # endif ) {
 sc -> ttf_glyph = j ;
 bygid [ j ++ ] = sc -> orig_pos ;
 }
 }
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 SplineChar * sc = sf -> glyphs [ i ] ;
 if ( SCWorthOutputting ( sc ) && sc -> ttf_glyph == - 1 # if HANYANG && ( ! iscff || ! sc -> compositionunit ) # endif ) {
 sc -> ttf_glyph = j ;
 bygid [ j ++ ] = i ;
 }
 }
 gi -> bygid = bygid ;
 gi -> gcnt = j ;
 return j ;
 }