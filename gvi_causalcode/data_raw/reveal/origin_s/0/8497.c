static inline int64_t systick_scale ( nvic_state * s ) {
 if ( s -> systick . control & SYSTICK_CLKSOURCE ) return system_clock_scale ;
 else return 1000 ;
 }