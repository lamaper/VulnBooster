static void dumpcffnames ( SplineFont * sf , FILE * cfff ) {
 char * pt ;
 putshort ( cfff , 1 ) ;
 putc ( '\1' , cfff ) ;
 putc ( '\1' , cfff ) ;
 putc ( '\1' + strlen ( sf -> fontname ) , cfff ) ;
 for ( pt = sf -> fontname ;
 * pt ;
 ++ pt ) putc ( * pt , cfff ) ;
 }