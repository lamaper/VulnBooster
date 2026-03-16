void cpu_enable_ticks ( void ) {
 if ( ! timers_state . cpu_ticks_enabled ) {
 timers_state . cpu_ticks_offset -= cpu_get_real_ticks ( ) ;
 timers_state . cpu_clock_offset -= get_clock ( ) ;
 timers_state . cpu_ticks_enabled = 1 ;
 }
 }