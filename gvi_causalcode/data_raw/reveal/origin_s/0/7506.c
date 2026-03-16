static void tcg_signal_cpu_creation ( CPUState * cpu , void * data ) {
 cpu -> thread_id = qemu_get_thread_id ( ) ;
 cpu -> created = true ;
 }