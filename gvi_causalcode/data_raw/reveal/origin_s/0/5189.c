static void putu24 ( FILE * file , int val ) {
 putc ( ( val >> 16 ) & 0xff , file ) ;
 putc ( ( val >> 8 ) & 0xff , file ) ;
 putc ( val & 0xff , file ) ;
 }