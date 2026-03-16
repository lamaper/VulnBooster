bool qemu_cpu_is_self ( CPUState * cpu ) {
 return qemu_thread_is_self ( cpu -> thread ) ;
 }