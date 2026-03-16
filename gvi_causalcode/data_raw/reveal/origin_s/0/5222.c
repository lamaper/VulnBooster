static inline int get_current_cpu ( ARMMPTimerState * s ) {
 if ( current_cpu -> cpu_index >= s -> num_cpu ) {
 hw_error ( "arm_mptimer: num-cpu %d but this cpu is %d!\n" , s -> num_cpu , current_cpu -> cpu_index ) ;
 }
 return current_cpu -> cpu_index ;
 }