static void dumpcffdictindex ( SplineFont * sf , struct alltabs * at ) {
 int i ;
 int pos ;
 putshort ( at -> fdarray , sf -> subfontcnt ) ;
 putc ( '\2' , at -> fdarray ) ;
 putshort ( at -> fdarray , 1 ) ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) putshort ( at -> fdarray , 0 ) ;
 pos = ftell ( at -> fdarray ) - 1 ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) {
 at -> fds [ i ] . fillindictmark = dumpcffdict ( sf -> subfonts [ i ] , at ) ;
 at -> fds [ i ] . eodictmark = ftell ( at -> fdarray ) ;
 if ( at -> fds [ i ] . eodictmark > 65536 ) IError ( "The DICT INDEX got too big, result won't work" ) ;
 }
 fseek ( at -> fdarray , 2 * sizeof ( short ) + sizeof ( char ) , SEEK_SET ) ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) putshort ( at -> fdarray , at -> fds [ i ] . eodictmark - pos ) ;
 fseek ( at -> fdarray , 0 , SEEK_END ) ;
 }