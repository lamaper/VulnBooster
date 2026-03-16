static void timerblock_reload ( TimerBlock * tb , int restart ) {
 if ( tb -> count == 0 ) {
 return ;
 }
 if ( restart ) {
 tb -> tick = qemu_get_clock_ns ( vm_clock ) ;
 }
 tb -> tick += ( int64_t ) tb -> count * timerblock_scale ( tb ) ;
 qemu_mod_timer ( tb -> timer , tb -> tick ) ;
 }