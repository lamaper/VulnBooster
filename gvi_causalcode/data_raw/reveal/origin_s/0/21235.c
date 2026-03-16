static void arm_thistimer_write ( void * opaque , hwaddr addr , uint64_t value , unsigned size ) {
 ARMMPTimerState * s = ( ARMMPTimerState * ) opaque ;
 int id = get_current_cpu ( s ) ;
 timerblock_write ( & s -> timerblock [ id ] , addr , value , size ) ;
 }