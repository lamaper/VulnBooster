int AlreadyMSSymbolArea ( SplineFont * sf , EncMap * map ) {
 int i ;
 int acnt = 0 , pcnt = 0 ;
 for ( i = 0 ;
 i < map -> enccount && i < 0xffff ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && sf -> glyphs [ map -> map [ i ] ] != NULL && sf -> glyphs [ map -> map [ i ] ] -> ttf_glyph != - 1 ) {
 if ( i >= 0xf000 && i <= 0xf0ff ) ++ pcnt ;
 else if ( i >= 0x20 && i <= 0xff ) ++ acnt ;
 }
 }
 return ( pcnt > acnt ) ;
 }