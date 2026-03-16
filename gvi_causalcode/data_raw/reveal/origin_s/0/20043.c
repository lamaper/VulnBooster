static void dumpsizedint ( FILE * cfff , int big , int num , int oper ) {
 if ( big ) {
 putc ( 29 , cfff ) ;
 putc ( ( num >> 24 ) & 0xff , cfff ) ;
 putc ( ( num >> 16 ) & 0xff , cfff ) ;
 putc ( ( num >> 8 ) & 0xff , cfff ) ;
 putc ( num & 0xff , cfff ) ;
 }
 else {
 putc ( 28 , cfff ) ;
 putc ( num >> 8 , cfff ) ;
 putc ( num & 0xff , cfff ) ;
 }
 dumpoper ( cfff , oper ) ;
 }