void resume_all_vcpus ( void ) {
 CPUArchState * penv = first_cpu ;
 qemu_clock_enable ( vm_clock , true ) ;
 while ( penv ) {
 CPUState * pcpu = ENV_GET_CPU ( penv ) ;
 cpu_resume ( pcpu ) ;
 penv = penv -> next_cpu ;
 }
 }