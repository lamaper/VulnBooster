static uint64_t arm_thistimer_read ( void * opaque , hwaddr addr , unsigned size ) {
 ARMMPTimerState * s = ( ARMMPTimerState * ) opaque ;
 int id = get_current_cpu ( s ) ;
 return timerblock_read ( & s -> timerblock [ id ] , addr , size ) ;
 }