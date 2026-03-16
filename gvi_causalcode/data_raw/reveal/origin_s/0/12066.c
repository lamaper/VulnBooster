static void AssignNotdefNull ( SplineFont * sf , int * bygid , int iscff ) {
 int i ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 if ( bygid [ 0 ] == - 1 && strcmp ( sf -> glyphs [ i ] -> name , ".notdef" ) == 0 ) {
 sf -> glyphs [ i ] -> ttf_glyph = 0 ;
 bygid [ 0 ] = i ;
 }
 else if ( ! iscff && bygid [ 1 ] == - 1 && ( strcmp ( sf -> glyphs [ i ] -> name , ".null" ) == 0 || strcmp ( sf -> glyphs [ i ] -> name , "uni0000" ) == 0 || ( i == 1 && strcmp ( sf -> glyphs [ 1 ] -> name , "glyph1" ) == 0 ) ) ) {
 sf -> glyphs [ i ] -> ttf_glyph = 1 ;
 bygid [ 1 ] = i ;
 }
 else if ( ! iscff && bygid [ 2 ] == - 1 && ( strcmp ( sf -> glyphs [ i ] -> name , "nonmarkingreturn" ) == 0 || strcmp ( sf -> glyphs [ i ] -> name , "uni000D" ) == 0 || ( i == 2 && strcmp ( sf -> glyphs [ 2 ] -> name , "glyph2" ) == 0 ) ) ) {
 sf -> glyphs [ i ] -> ttf_glyph = 2 ;
 bygid [ 2 ] = i ;
 }
 }
 }