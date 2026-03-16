static void ATFigureDefWidth ( SplineFont * sf , struct alltabs * at , int subfont ) {
 int nomwid , defwid ;
 defwid = SFFigureDefWidth ( sf , & nomwid ) ;
 if ( subfont == - 1 ) at -> defwid = defwid ;
 else at -> fds [ subfont ] . defwid = defwid ;
 if ( subfont == - 1 ) at -> nomwid = nomwid ;
 else at -> fds [ subfont ] . nomwid = nomwid ;
 }