static void malta_fpga_reset ( void * opaque ) {
 MaltaFPGAState * s = opaque ;
 s -> leds = 0x00 ;
 s -> brk = 0x0a ;
 s -> gpout = 0x00 ;
 s -> i2cin = 0x3 ;
 s -> i2coe = 0x0 ;
 s -> i2cout = 0x3 ;
 s -> i2csel = 0x1 ;
 s -> display_text [ 8 ] = '\0' ;
 snprintf ( s -> display_text , 9 , " " ) ;
 }