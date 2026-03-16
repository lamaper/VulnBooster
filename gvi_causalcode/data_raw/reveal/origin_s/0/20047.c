void SFDummyUpCIDs ( struct glyphinfo * gi , SplineFont * sf ) {
 int i , j , k , max ;
 int * bygid ;
 max = 0 ;
 for ( k = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) if ( sf -> subfonts [ k ] -> glyphcnt > max ) max = sf -> subfonts [ k ] -> glyphcnt ;
 if ( max == 0 ) return ;
 sf -> glyphs = calloc ( max , sizeof ( SplineChar * ) ) ;
 sf -> glyphcnt = sf -> glyphmax = max ;
 for ( k = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) for ( i = 0 ;
 i < sf -> subfonts [ k ] -> glyphcnt ;
 ++ i ) if ( sf -> subfonts [ k ] -> glyphs [ i ] != NULL ) sf -> glyphs [ i ] = sf -> subfonts [ k ] -> glyphs [ i ] ;
 if ( gi == NULL ) return ;
 bygid = malloc ( ( sf -> glyphcnt + 3 ) * sizeof ( int ) ) ;
 memset ( bygid , 0xff , ( sf -> glyphcnt + 3 ) * sizeof ( int ) ) ;
 j = 1 ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 if ( bygid [ 0 ] == - 1 && strcmp ( sf -> glyphs [ i ] -> name , ".notdef" ) == 0 ) {
 sf -> glyphs [ i ] -> ttf_glyph = 0 ;
 bygid [ 0 ] = i ;
 }
 else if ( SCWorthOutputting ( sf -> glyphs [ i ] ) ) {
 sf -> glyphs [ i ] -> ttf_glyph = j ;
 bygid [ j ++ ] = i ;
 }
 }
 gi -> bygid = bygid ;
 gi -> gcnt = j ;
 }