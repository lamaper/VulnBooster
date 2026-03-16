void cpu_disable_ticks ( void ) {
 if ( timers_state . cpu_ticks_enabled ) {
 timers_state . cpu_ticks_offset = cpu_get_ticks ( ) ;
 timers_state . cpu_clock_offset = cpu_get_clock ( ) ;
 timers_state . cpu_ticks_enabled = 0 ;
 }
 }