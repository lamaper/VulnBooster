static void qemu_kvm_wait_io_event ( CPUState * cpu ) {
 while ( cpu_thread_is_idle ( cpu ) ) {
 qemu_cond_wait ( cpu -> halt_cond , & qemu_global_mutex ) ;
 }
 qemu_kvm_eat_signals ( cpu ) ;
 qemu_wait_io_event_common ( cpu ) ;
 }