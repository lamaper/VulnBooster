static void qemu_tcg_init_vcpu ( CPUState * cpu ) {
 if ( ! tcg_cpu_thread ) {
 cpu -> thread = g_malloc0 ( sizeof ( QemuThread ) ) ;
 cpu -> halt_cond = g_malloc0 ( sizeof ( QemuCond ) ) ;
 qemu_cond_init ( cpu -> halt_cond ) ;
 tcg_halt_cond = cpu -> halt_cond ;
 qemu_thread_create ( cpu -> thread , qemu_tcg_cpu_thread_fn , cpu , QEMU_THREAD_JOINABLE ) ;


 qemu_cond_wait ( & qemu_cpu_cond , & qemu_global_mutex ) ;
 }
 tcg_cpu_thread = cpu -> thread ;
 }
 else {
 cpu -> thread = tcg_cpu_thread ;
 cpu -> halt_cond = tcg_halt_cond ;
 }
 }