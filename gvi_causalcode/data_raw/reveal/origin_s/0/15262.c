static void dumpoffset ( FILE * file , int offsize , int val ) {
 if ( offsize == 1 ) putc ( val , file ) ;
 else if ( offsize == 2 ) putshort ( file , val ) ;
 else if ( offsize == 3 ) {
 putc ( ( val >> 16 ) & 0xff , file ) ;
 putc ( ( val >> 8 ) & 0xff , file ) ;
 putc ( val & 0xff , file ) ;
 }
 else putlong ( file , val ) ;
 }