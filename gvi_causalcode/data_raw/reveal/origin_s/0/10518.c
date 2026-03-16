void cpu_synchronize_all_post_reset ( void ) {
 CPUArchState * cpu ;
 for ( cpu = first_cpu ;
 cpu ;
 cpu = cpu -> next_cpu ) {
 cpu_synchronize_post_reset ( ENV_GET_CPU ( cpu ) ) ;
 }
 }