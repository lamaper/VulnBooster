static void pcnet_stop ( PCNetState * s ) {


 s -> csr [ 0 ] |= 0x0014 ;
 s -> csr [ 4 ] &= ~ 0x02c2 ;
 s -> csr [ 5 ] &= ~ 0x0011 ;
 pcnet_poll_timer ( s ) ;
 }