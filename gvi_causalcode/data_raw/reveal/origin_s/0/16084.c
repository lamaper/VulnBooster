static int pxa2xx_i2c_tx ( I2CSlave * i2c , uint8_t data ) {
 PXA2xxI2CSlaveState * slave = FROM_I2C_SLAVE ( PXA2xxI2CSlaveState , i2c ) ;
 PXA2xxI2CState * s = slave -> host ;
 if ( ( s -> control & ( 1 << 14 ) ) || ! ( s -> control & ( 1 << 6 ) ) ) return 1 ;
 if ( ! ( s -> status & ( 1 << 0 ) ) ) {
 s -> status |= 1 << 7 ;
 s -> data = data ;
 }
 pxa2xx_i2c_update ( s ) ;
 return 1 ;
 }