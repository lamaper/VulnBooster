static int AssignTTFBitGlyph ( struct glyphinfo * gi , SplineFont * sf , EncMap * map , int32 * bsizes ) {
 int i , j ;
 BDFFont * bdf ;
 int * bygid = malloc ( ( sf -> glyphcnt + 3 ) * sizeof ( int ) ) ;
 memset ( bygid , 0xff , ( sf -> glyphcnt + 3 ) * sizeof ( int ) ) ;
 AssignNotdefNull ( sf , bygid , false ) ;
 for ( bdf = sf -> bitmaps ;
 bdf != NULL ;
 bdf = bdf -> next ) {
 for ( j = 0 ;
 bsizes [ j ] != 0 && ( ( bsizes [ j ] & 0xffff ) != bdf -> pixelsize || ( bsizes [ j ] >> 16 ) != BDFDepth ( bdf ) ) ;
 ++ j ) ;
 if ( bsizes [ j ] == 0 ) continue ;
 for ( i = 0 ;
 i < bdf -> glyphcnt ;
 ++ i ) if ( ! IsntBDFChar ( bdf -> glyphs [ i ] ) ) sf -> glyphs [ i ] -> ttf_glyph = - 2 ;
 }
 j = 3 ;
 for ( i = 0 ;
 i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 ) {
 SplineChar * sc = sf -> glyphs [ map -> map [ i ] ] ;
 if ( sc -> ttf_glyph == - 2 ) {
 sc -> ttf_glyph = j ;
 bygid [ j ++ ] = sc -> orig_pos ;
 }
 }
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 SplineChar * sc = sf -> glyphs [ i ] ;
 if ( sc -> ttf_glyph == - 2 ) {
 sc -> ttf_glyph = j ;
 bygid [ j ++ ] = i ;
 }
 }
 gi -> bygid = bygid ;
 gi -> gcnt = j ;
 return j ;
 }