static void typhoon_alarm_timer ( void * opaque ) {
 TyphoonState * s = ( TyphoonState * ) ( ( uintptr_t ) opaque & ~ 3 ) ;
 int cpu = ( uintptr_t ) opaque & 3 ;
 s -> cchip . misc |= 1 << ( cpu + 4 ) ;
 cpu_interrupt ( CPU ( s -> cchip . cpu [ cpu ] ) , CPU_INTERRUPT_TIMER ) ;
 }