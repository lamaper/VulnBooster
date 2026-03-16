static void qemu_kvm_start_vcpu ( CPUState * cpu ) {
 cpu -> thread = g_malloc0 ( sizeof ( QemuThread ) ) ;
 cpu -> halt_cond = g_malloc0 ( sizeof ( QemuCond ) ) ;
 qemu_cond_init ( cpu -> halt_cond ) ;
 qemu_thread_create ( cpu -> thread , qemu_kvm_cpu_thread_fn , cpu , QEMU_THREAD_JOINABLE ) ;
 while ( ! cpu -> created ) {
 qemu_cond_wait ( & qemu_cpu_cond , & qemu_global_mutex ) ;
 }
 }