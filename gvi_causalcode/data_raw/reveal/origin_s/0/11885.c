static int isStdEncoding ( SplineFont * sf , EncMap * map ) {
 int i ;
 for ( i = 0 ;
 i < 256 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && sf -> glyphs [ map -> map [ i ] ] != NULL ) if ( sf -> glyphs [ map -> map [ i ] ] -> unicodeenc != - 1 ) if ( sf -> glyphs [ map -> map [ i ] ] -> unicodeenc != unicode_from_adobestd [ i ] ) return ( 0 ) ;
 return ( 1 ) ;
 }