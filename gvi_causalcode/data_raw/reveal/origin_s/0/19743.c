static void dumpcffcidset ( struct alltabs * at ) {
 int gid , start ;
 putc ( 2 , at -> charset ) ;
 start = - 1 ;
 for ( gid = 1 ;
 gid < at -> gi . gcnt ;
 ++ gid ) {
 if ( start == - 1 ) start = gid ;
 else if ( at -> gi . bygid [ gid ] - at -> gi . bygid [ start ] != gid - start ) {
 putshort ( at -> charset , at -> gi . bygid [ start ] ) ;
 putshort ( at -> charset , at -> gi . bygid [ gid - 1 ] - at -> gi . bygid [ start ] ) ;
 start = gid ;
 }
 }
 if ( start != - 1 ) {
 putshort ( at -> charset , at -> gi . bygid [ start ] ) ;
 putshort ( at -> charset , at -> gi . bygid [ gid - 1 ] - at -> gi . bygid [ start ] ) ;
 }
 }