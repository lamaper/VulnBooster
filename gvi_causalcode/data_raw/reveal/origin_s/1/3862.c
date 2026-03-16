static void cpu_halt_signal ( void * opaque , int irq , int level ) {
 if ( level && cpu_single_env ) {
 cpu_interrupt ( CPU ( sparc_env_get_cpu ( cpu_single_env ) ) , CPU_INTERRUPT_HALT ) ;
 }
 }