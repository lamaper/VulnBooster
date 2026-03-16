static void secondary_cpu_reset ( void * opaque ) {
 SPARCCPU * cpu = opaque ;
 CPUState * cs = CPU ( cpu ) ;
 cpu_reset ( cs ) ;
 cs -> halted = 1 ;
 }