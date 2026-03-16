void qemu_init_cpu_loop ( void ) {
 qemu_init_sigbus ( ) ;
 qemu_cond_init ( & qemu_cpu_cond ) ;
 qemu_cond_init ( & qemu_pause_cond ) ;
 qemu_cond_init ( & qemu_work_cond ) ;
 qemu_cond_init ( & qemu_io_proceeded_cond ) ;
 qemu_mutex_init ( & qemu_global_mutex ) ;
 qemu_thread_get_self ( & io_thread ) ;
 }