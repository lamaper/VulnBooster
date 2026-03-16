void putlong ( FILE * file , int val ) {
 putc ( ( val >> 24 ) & 0xff , file ) ;
 putc ( ( val >> 16 ) & 0xff , file ) ;
 putc ( ( val >> 8 ) & 0xff , file ) ;
 putc ( val & 0xff , file ) ;
 }