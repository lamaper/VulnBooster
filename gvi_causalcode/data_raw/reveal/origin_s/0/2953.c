void cpu_synchronize_all_states ( void ) {
 CPUArchState * env ;
 for ( env = first_cpu ;
 env ;
 env = env -> next_cpu ) {
 cpu_synchronize_state ( ENV_GET_CPU ( env ) ) ;
 }
 }