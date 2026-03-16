void qemu_cpu_kick ( CPUState * cpu ) {
 qemu_cond_broadcast ( cpu -> halt_cond ) ;
 if ( ! tcg_enabled ( ) && ! cpu -> thread_kicked ) {
 qemu_cpu_kick_thread ( cpu ) ;
 cpu -> thread_kicked = true ;
 }
 }