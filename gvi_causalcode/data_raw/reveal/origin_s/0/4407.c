static void redoloca ( struct alltabs * at ) {
 int i ;
 at -> loca = tmpfile ( ) ;
 if ( at -> head . locais32 ) {
 for ( i = 0 ;
 i <= at -> maxp . numGlyphs ;
 ++ i ) putlong ( at -> loca , at -> gi . loca [ i ] ) ;
 at -> localen = sizeof ( int32 ) * ( at -> maxp . numGlyphs + 1 ) ;
 }
 else {
 for ( i = 0 ;
 i <= at -> maxp . numGlyphs ;
 ++ i ) putshort ( at -> loca , at -> gi . loca [ i ] / 2 ) ;
 at -> localen = sizeof ( int16 ) * ( at -> maxp . numGlyphs + 1 ) ;
 if ( ftell ( at -> loca ) & 2 ) putshort ( at -> loca , 0 ) ;
 }
 if ( at -> format != ff_type42 && at -> format != ff_type42cid ) {
 free ( at -> gi . loca ) ;
 at -> gi . loca = NULL ;
 }
 }