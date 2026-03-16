static void cpu_irq_change ( AlphaCPU * cpu , uint64_t req ) {
 if ( cpu != NULL ) {
 CPUState * cs = CPU ( cpu ) ;
 if ( req ) {
 cpu_interrupt ( cs , CPU_INTERRUPT_HARD ) ;
 }
 else {
 cpu_reset_interrupt ( cs , CPU_INTERRUPT_HARD ) ;
 }
 }
 }