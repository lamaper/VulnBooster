static int kvm_handle_debug ( X86CPU * cpu , struct kvm_debug_exit_arch * arch_info ) {
 CPUState * cs = CPU ( cpu ) ;
 CPUX86State * env = & cpu -> env ;
 int ret = 0 ;
 int n ;
 if ( arch_info -> exception == 1 ) {
 if ( arch_info -> dr6 & ( 1 << 14 ) ) {
 if ( cs -> singlestep_enabled ) {
 ret = EXCP_DEBUG ;
 }
 }
 else {
 for ( n = 0 ;
 n < 4 ;
 n ++ ) {
 if ( arch_info -> dr6 & ( 1 << n ) ) {
 switch ( ( arch_info -> dr7 >> ( 16 + n * 4 ) ) & 0x3 ) {
 case 0x0 : ret = EXCP_DEBUG ;
 break ;
 case 0x1 : ret = EXCP_DEBUG ;
 cs -> watchpoint_hit = & hw_watchpoint ;
 hw_watchpoint . vaddr = hw_breakpoint [ n ] . addr ;
 hw_watchpoint . flags = BP_MEM_WRITE ;
 break ;
 case 0x3 : ret = EXCP_DEBUG ;
 cs -> watchpoint_hit = & hw_watchpoint ;
 hw_watchpoint . vaddr = hw_breakpoint [ n ] . addr ;
 hw_watchpoint . flags = BP_MEM_ACCESS ;
 break ;
 }
 }
 }
 }
 }
 else if ( kvm_find_sw_breakpoint ( cs , arch_info -> pc ) ) {
 ret = EXCP_DEBUG ;
 }
 if ( ret == 0 ) {
 cpu_synchronize_state ( cs ) ;
 assert ( env -> exception_injected == - 1 ) ;
 env -> exception_injected = arch_info -> exception ;
 env -> has_error_code = 0 ;
 }
 return ret ;
 }