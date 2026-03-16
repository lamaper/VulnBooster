CPUState * s390_cpu_addr2state ( uint16_t cpu_addr ) {
 if ( cpu_addr >= smp_cpus ) {
 return NULL ;
 }
 return ipi_states [ cpu_addr ] ;
 }