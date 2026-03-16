void cpu_stop_current ( void ) {
 if ( current_cpu ) {
 current_cpu -> stop = false ;
 current_cpu -> stopped = true ;
 cpu_exit ( current_cpu ) ;
 qemu_cond_signal ( & qemu_pause_cond ) ;
 }
 }