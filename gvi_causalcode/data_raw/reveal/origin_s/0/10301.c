void set_numa_modes ( void ) {
 CPUArchState * env ;
 CPUState * cpu ;
 int i ;
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 cpu = ENV_GET_CPU ( env ) ;
 for ( i = 0 ;
 i < nb_numa_nodes ;
 i ++ ) {
 if ( test_bit ( cpu -> cpu_index , node_cpumask [ i ] ) ) {
 cpu -> numa_node = i ;
 }
 }
 }
 }