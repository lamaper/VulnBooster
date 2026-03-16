static void tcg_exec_all ( void ) {
 int r ;
 qemu_clock_warp ( vm_clock ) ;
 if ( next_cpu == NULL ) {
 next_cpu = first_cpu ;
 }
 for ( ;
 next_cpu != NULL && ! exit_request ;
 next_cpu = next_cpu -> next_cpu ) {
 CPUArchState * env = next_cpu ;
 CPUState * cpu = ENV_GET_CPU ( env ) ;
 qemu_clock_enable ( vm_clock , ( env -> singlestep_enabled & SSTEP_NOTIMER ) == 0 ) ;
 if ( cpu_can_run ( cpu ) ) {
 r = tcg_cpu_exec ( env ) ;
 if ( r == EXCP_DEBUG ) {
 cpu_handle_guest_debug ( cpu ) ;
 break ;
 }
 }
 else if ( cpu -> stop || cpu -> stopped ) {
 break ;
 }
 }
 exit_request = 0 ;
 }