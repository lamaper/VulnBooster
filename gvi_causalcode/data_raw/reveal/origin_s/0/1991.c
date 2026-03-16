void qemu_cpu_kick_self ( void ) {

 if ( ! current_cpu -> thread_kicked ) {
 qemu_cpu_kick_thread ( current_cpu ) ;
 current_cpu -> thread_kicked = true ;
 }

