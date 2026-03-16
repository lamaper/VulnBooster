static void main_cpu_reset ( void * opaque ) {
 MIPSCPU * cpu = opaque ;
 cpu_reset ( CPU ( cpu ) ) ;
 }