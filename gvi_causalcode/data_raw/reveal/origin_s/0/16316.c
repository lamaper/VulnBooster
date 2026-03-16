static void timerblock_tick ( void * opaque ) {
 TimerBlock * tb = ( TimerBlock * ) opaque ;
 tb -> status = 1 ;
 if ( tb -> control & 2 ) {
 tb -> count = tb -> load ;
 timerblock_reload ( tb , 0 ) ;
 }
 else {
 tb -> count = 0 ;
 }
 timerblock_update_irq ( tb ) ;
 }