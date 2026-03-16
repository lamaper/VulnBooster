static void dumpcffcharset ( SplineFont * sf , struct alltabs * at ) {
 int i ;
 at -> gn_sid = calloc ( at -> gi . gcnt , sizeof ( uint32 ) ) ;
 putc ( 0 , at -> charset ) ;
 for ( i = 1 ;
 i < at -> gi . gcnt ;
 ++ i ) if ( at -> gi . bygid [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ at -> gi . bygid [ i ] ] ) ) {
 at -> gn_sid [ i ] = storesid ( at , sf -> glyphs [ at -> gi . bygid [ i ] ] -> name ) ;
 putshort ( at -> charset , at -> gn_sid [ i ] ) ;
 }
 }