static void systick_timer_tick ( void * opaque ) {
 nvic_state * s = ( nvic_state * ) opaque ;
 s -> systick . control |= SYSTICK_COUNTFLAG ;
 if ( s -> systick . control & SYSTICK_TICKINT ) {
 armv7m_nvic_set_pending ( s , ARMV7M_EXCP_SYSTICK ) ;
 }
 if ( s -> systick . reload == 0 ) {
 s -> systick . control &= ~ SYSTICK_ENABLE ;
 }
 else {
 systick_reload ( s , 0 ) ;
 }
 }