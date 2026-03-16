static void cpu_halt_signal ( void * opaque , int irq , int level ) {
 if ( level && current_cpu ) {
 cpu_interrupt ( current_cpu , CPU_INTERRUPT_HALT ) ;
 }
 }