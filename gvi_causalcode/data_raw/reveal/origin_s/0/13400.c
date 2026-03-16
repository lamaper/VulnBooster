static void dummyloca ( struct alltabs * at ) {
 at -> loca = tmpfile ( ) ;
 if ( at -> head . locais32 ) {
 putlong ( at -> loca , 0 ) ;
 at -> localen = sizeof ( int32 ) ;
 }
 else {
 putshort ( at -> loca , 0 ) ;
 at -> localen = sizeof ( int16 ) ;
 putshort ( at -> loca , 0 ) ;
 }
 }