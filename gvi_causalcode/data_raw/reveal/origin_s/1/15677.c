static void cpu_request_exit ( void * opaque , int irq , int level ) {
 CPUPPCState * env = cpu_single_env ;
 if ( env && level ) {
 cpu_exit ( CPU ( ppc_env_get_cpu ( env ) ) ) ;
 }
 }