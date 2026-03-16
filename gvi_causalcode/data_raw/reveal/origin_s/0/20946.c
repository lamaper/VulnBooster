static void dumpint ( FILE * cfff , int num ) {
 if ( num >= - 107 && num <= 107 ) putc ( num + 139 , cfff ) ;
 else if ( num >= 108 && num <= 1131 ) {
 num -= 108 ;
 putc ( ( num >> 8 ) + 247 , cfff ) ;
 putc ( num & 0xff , cfff ) ;
 }
 else if ( num >= - 1131 && num <= - 108 ) {
 num = - num ;
 num -= 108 ;
 putc ( ( num >> 8 ) + 251 , cfff ) ;
 putc ( num & 0xff , cfff ) ;
 }
 else if ( num >= - 32768 && num < 32768 ) {
 putc ( 28 , cfff ) ;
 putc ( num >> 8 , cfff ) ;
 putc ( num & 0xff , cfff ) ;
 }
 else {
 putc ( 29 , cfff ) ;
 putc ( ( num >> 24 ) & 0xff , cfff ) ;
 putc ( ( num >> 16 ) & 0xff , cfff ) ;
 putc ( ( num >> 8 ) & 0xff , cfff ) ;
 putc ( num & 0xff , cfff ) ;
 }
 }