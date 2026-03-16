static inline int get_current_cpu ( ARMMPTimerState * s ) {
 CPUState * cpu_single_cpu = ENV_GET_CPU ( cpu_single_env ) ;
 if ( cpu_single_cpu -> cpu_index >= s -> num_cpu ) {
 hw_error ( "arm_mptimer: num-cpu %d but this cpu is %d!\n" , s -> num_cpu , cpu_single_cpu -> cpu_index ) ;
 }
 return cpu_single_cpu -> cpu_index ;
 }