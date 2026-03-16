static void typhoon_set_irq ( void * opaque , int irq , int level ) {
 TyphoonState * s = opaque ;
 uint64_t drir ;
 int i ;
 drir = s -> cchip . drir ;
 if ( level ) {
 drir |= 1ull << irq ;
 }
 else {
 drir &= ~ ( 1ull << irq ) ;
 }
 s -> cchip . drir = drir ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 cpu_irq_change ( s -> cchip . cpu [ i ] , s -> cchip . dim [ i ] & drir ) ;
 }
 }