void cpu_synchronize_all_post_init ( void ) {
 CPUArchState * cpu ;
 for ( cpu = first_cpu ;
 cpu ;
 cpu = cpu -> next_cpu ) {
 cpu_synchronize_post_init ( ENV_GET_CPU ( cpu ) ) ;
 }
 }