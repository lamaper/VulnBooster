int cpu_signal_handler ( int host_signum , void * pinfo , void * puc ) {
 siginfo_t * info = pinfo ;
 unsigned long pc ;




 return handle_cpu_signal ( pc , ( unsigned long ) info -> si_addr , TRAP_sig ( uc ) == 0xe ? ( ERROR_sig ( uc ) >> 1 ) & 1 : 0 , & MASK_sig ( uc ) , puc ) ;
 }