static int AnyInstructions ( SplineFont * sf ) {
 int i ;
 if ( sf -> subfontcnt != 0 ) {
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) if ( AnyInstructions ( sf -> subfonts [ i ] ) ) return ( true ) ;
 }
 else {
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 if ( sf -> glyphs [ i ] -> ttf_instrs_len != 0 ) return ( true ) ;
 }
 }
 return ( false ) ;
 }