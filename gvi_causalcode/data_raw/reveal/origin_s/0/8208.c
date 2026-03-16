static void main_cpu_reset ( void * opaque ) {
 SPARCCPU * cpu = opaque ;
 CPUState * cs = CPU ( cpu ) ;
 cpu_reset ( cs ) ;
 cs -> halted = 0 ;
 }