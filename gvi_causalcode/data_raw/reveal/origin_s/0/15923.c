void cpu_loop_exit ( CPUArchState * env ) {
 CPUState * cpu = ENV_GET_CPU ( env ) ;
 cpu -> current_tb = NULL ;
 siglongjmp ( env -> jmp_env , 1 ) ;
 }