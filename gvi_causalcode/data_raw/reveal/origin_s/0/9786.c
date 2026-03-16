static void typhoon_set_timer_irq ( void * opaque , int irq , int level ) {
 TyphoonState * s = opaque ;
 int i ;
 if ( level == 0 ) {
 return ;
 }
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 AlphaCPU * cpu = s -> cchip . cpu [ i ] ;
 if ( cpu != NULL ) {
 uint32_t iic = s -> cchip . iic [ i ] ;
 iic = ( ( iic - 1 ) & 0x1ffffff ) | ( iic & 0x1000000 ) ;
 s -> cchip . iic [ i ] = iic ;
 if ( iic & 0x1000000 ) {
 s -> cchip . misc |= 1 << ( i + 4 ) ;
 cpu_interrupt ( CPU ( cpu ) , CPU_INTERRUPT_TIMER ) ;
 }
 }
 }
 }