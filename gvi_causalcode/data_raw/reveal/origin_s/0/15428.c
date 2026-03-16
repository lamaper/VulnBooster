static void dumpcfffdselect ( SplineFont * sf , struct alltabs * at ) {
 int cid , k , lastfd , cnt ;
 int gid ;
 putc ( 3 , at -> fdselect ) ;
 putshort ( at -> fdselect , 0 ) ;
 for ( k = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) if ( SCWorthOutputting ( sf -> subfonts [ k ] -> glyphs [ 0 ] ) ) break ;
 if ( k == sf -> subfontcnt ) -- k ;
 putshort ( at -> fdselect , 0 ) ;
 putc ( k , at -> fdselect ) ;
 lastfd = k ;
 cnt = 1 ;
 for ( gid = 1 ;
 gid < at -> gi . gcnt ;
 ++ gid ) {
 cid = at -> gi . bygid [ gid ] ;
 for ( k = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) {
 if ( cid < sf -> subfonts [ k ] -> glyphcnt && SCWorthOutputting ( sf -> subfonts [ k ] -> glyphs [ cid ] ) ) break ;
 }
 if ( k == sf -> subfontcnt ) ;
 else {
 if ( k != lastfd ) {
 putshort ( at -> fdselect , gid ) ;
 putc ( k , at -> fdselect ) ;
 lastfd = k ;
 ++ cnt ;
 }
 }
 }
 putshort ( at -> fdselect , gid ) ;
 fseek ( at -> fdselect , 1 , SEEK_SET ) ;
 putshort ( at -> fdselect , cnt ) ;
 fseek ( at -> fdselect , 0 , SEEK_END ) ;
 }