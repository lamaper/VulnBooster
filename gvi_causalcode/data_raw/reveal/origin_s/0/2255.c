static void * qemu_tcg_cpu_thread_fn ( void * arg ) {
 CPUState * cpu = arg ;
 CPUArchState * env ;
 qemu_tcg_init_cpu_signals ( ) ;
 qemu_thread_get_self ( cpu -> thread ) ;
 qemu_mutex_lock ( & qemu_global_mutex ) ;
 qemu_for_each_cpu ( tcg_signal_cpu_creation , NULL ) ;
 qemu_cond_signal ( & qemu_cpu_cond ) ;
 while ( ENV_GET_CPU ( first_cpu ) -> stopped ) {
 qemu_cond_wait ( tcg_halt_cond , & qemu_global_mutex ) ;
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 qemu_wait_io_event_common ( ENV_GET_CPU ( env ) ) ;
 }
 }
 while ( 1 ) {
 tcg_exec_all ( ) ;
 if ( use_icount && qemu_clock_deadline ( vm_clock ) <= 0 ) {
 qemu_notify_event ( ) ;
 }
 qemu_tcg_wait_io_event ( ) ;
 }
 return NULL ;
 }