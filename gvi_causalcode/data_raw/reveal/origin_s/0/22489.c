int SFHasInstructions ( SplineFont * sf ) {
 int i ;
 if ( sf -> mm != NULL && sf -> mm -> apple ) sf = sf -> mm -> normal ;
 if ( sf -> subfontcnt != 0 ) return ( false ) ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 if ( strcmp ( sf -> glyphs [ i ] -> name , ".notdef" ) == 0 ) continue ;
 if ( sf -> glyphs [ i ] -> ttf_instrs != NULL ) return ( true ) ;
 }
 return ( false ) ;
 }