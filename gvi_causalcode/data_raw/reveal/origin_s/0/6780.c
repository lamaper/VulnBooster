static void dumpcffheader ( FILE * cfff ) {
 putc ( '\1' , cfff ) ;
 putc ( '\0' , cfff ) ;
 putc ( '\4' , cfff ) ;
 putc ( '\4' , cfff ) ;
 }