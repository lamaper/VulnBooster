void hw_error ( const char * fmt , ... ) {
 va_list ap ;
 CPUArchState * env ;
 CPUState * cpu ;
 va_start ( ap , fmt ) ;
 fprintf ( stderr , "qemu: hardware error: " ) ;
 vfprintf ( stderr , fmt , ap ) ;
 fprintf ( stderr , "\n" ) ;
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 cpu = ENV_GET_CPU ( env ) ;
 fprintf ( stderr , "CPU #%d:\n" , cpu -> cpu_index ) ;
 cpu_dump_state ( cpu , stderr , fprintf , CPU_DUMP_FPU ) ;
 }
 va_end ( ap ) ;
 abort ( ) ;
 }