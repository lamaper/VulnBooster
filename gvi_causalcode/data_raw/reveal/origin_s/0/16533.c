static void pxa2xx_i2c_update ( PXA2xxI2CState * s ) {
 uint16_t level = 0 ;
 level |= s -> status & s -> control & ( 1 << 10 ) ;
 level |= ( s -> status & ( 1 << 7 ) ) && ( s -> control & ( 1 << 9 ) ) ;
 level |= ( s -> status & ( 1 << 6 ) ) && ( s -> control & ( 1 << 8 ) ) ;
 level |= s -> status & ( 1 << 9 ) ;
 qemu_set_irq ( s -> irq , ! ! level ) ;
 }