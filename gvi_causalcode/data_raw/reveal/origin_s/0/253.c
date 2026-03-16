static void cpu_kick_irq ( SPARCCPU * cpu ) {
 CPUSPARCState * env = & cpu -> env ;
 CPUState * cs = CPU ( cpu ) ;
 cs -> halted = 0 ;
 cpu_check_irqs ( env ) ;
 qemu_cpu_kick ( cs ) ;
 }