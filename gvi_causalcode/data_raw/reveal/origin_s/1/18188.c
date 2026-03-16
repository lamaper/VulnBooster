void cpu_stop_current ( void ) {
 if ( cpu_single_env ) {
 CPUState * cpu_single_cpu = ENV_GET_CPU ( cpu_single_env ) ;
 cpu_single_cpu -> stop = false ;
 cpu_single_cpu -> stopped = true ;
 cpu_exit ( cpu_single_cpu ) ;
 qemu_cond_signal ( & qemu_pause_cond ) ;
 }
 }