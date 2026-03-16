static void qemu_tcg_wait_io_event ( void ) {
 CPUArchState * env ;
 while ( all_cpu_threads_idle ( ) ) {
 qemu_clock_warp ( vm_clock ) ;
 qemu_cond_wait ( tcg_halt_cond , & qemu_global_mutex ) ;
 }
 while ( iothread_requesting_mutex ) {
 qemu_cond_wait ( & qemu_io_proceeded_cond , & qemu_global_mutex ) ;
 }
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 qemu_wait_io_event_common ( ENV_GET_CPU ( env ) ) ;
 }
 }