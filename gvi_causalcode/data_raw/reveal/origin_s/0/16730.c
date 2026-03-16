static void malta_fpga_update_display ( void * opaque ) {
 char leds_text [ 9 ] ;
 int i ;
 MaltaFPGAState * s = opaque ;
 for ( i = 7 ;
 i >= 0 ;
 i -- ) {
 if ( s -> leds & ( 1 << i ) ) leds_text [ i ] = '#' ;
 else leds_text [ i ] = ' ' ;
 }
 leds_text [ 8 ] = '\0' ;
 qemu_chr_fe_printf ( s -> display , "\e[H\n\n|\e[32m%-8.8s\e[00m|\r\n" , leds_text ) ;
 qemu_chr_fe_printf ( s -> display , "\n\n\n\n|\e[31m%-8.8s\e[00m|" , s -> display_text ) ;
 }