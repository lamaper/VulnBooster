static void timerblock_reset ( TimerBlock * tb ) {
 tb -> count = 0 ;
 tb -> load = 0 ;
 tb -> control = 0 ;
 tb -> status = 0 ;
 tb -> tick = 0 ;
 if ( tb -> timer ) {
 qemu_del_timer ( tb -> timer ) ;
 }
 }