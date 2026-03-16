static inline void pxa2xx_fir_update ( PXA2xxFIrState * s ) {
 static const int tresh [ 4 ] = {
 8 , 16 , 32 , 0 }
 ;
 int intr = 0 ;
 if ( ( s -> control [ 0 ] & ( 1 << 4 ) ) && s -> rx_len >= tresh [ s -> control [ 2 ] & 3 ] ) s -> status [ 0 ] |= 1 << 4 ;
 else s -> status [ 0 ] &= ~ ( 1 << 4 ) ;
 if ( s -> control [ 0 ] & ( 1 << 3 ) ) s -> status [ 0 ] |= 1 << 3 ;
 else s -> status [ 0 ] &= ~ ( 1 << 3 ) ;
 if ( s -> rx_len ) s -> status [ 1 ] |= 1 << 2 ;
 else s -> status [ 1 ] &= ~ ( 1 << 2 ) ;
 if ( s -> control [ 0 ] & ( 1 << 4 ) ) s -> status [ 1 ] |= 1 << 0 ;
 else s -> status [ 1 ] &= ~ ( 1 << 0 ) ;
 intr |= ( s -> control [ 0 ] & ( 1 << 5 ) ) && ( s -> status [ 0 ] & ( 1 << 4 ) ) ;
 intr |= ( s -> control [ 0 ] & ( 1 << 6 ) ) && ( s -> status [ 0 ] & ( 1 << 3 ) ) ;
 intr |= ( s -> control [ 2 ] & ( 1 << 4 ) ) && ( s -> status [ 0 ] & ( 1 << 6 ) ) ;
 intr |= ( s -> control [ 0 ] & ( 1 << 2 ) ) && ( s -> status [ 0 ] & ( 1 << 1 ) ) ;
 intr |= s -> status [ 0 ] & 0x25 ;
 qemu_set_irq ( s -> rx_dma , ( s -> status [ 0 ] >> 4 ) & 1 ) ;
 qemu_set_irq ( s -> tx_dma , ( s -> status [ 0 ] >> 3 ) & 1 ) ;
 qemu_set_irq ( s -> irq , intr && s -> enable ) ;
 }