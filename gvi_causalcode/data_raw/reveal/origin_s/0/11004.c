static void dumpoper ( FILE * cfff , int oper ) {
 if ( oper != - 1 ) {
 if ( oper >= 256 ) putc ( oper >> 8 , cfff ) ;
 putc ( oper & 0xff , cfff ) ;
 }
 }