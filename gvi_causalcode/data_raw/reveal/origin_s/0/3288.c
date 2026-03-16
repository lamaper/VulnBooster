static int kvm_handle_halt ( X86CPU * cpu ) {
 CPUState * cs = CPU ( cpu ) ;
 CPUX86State * env = & cpu -> env ;
 if ( ! ( ( cs -> interrupt_request & CPU_INTERRUPT_HARD ) && ( env -> eflags & IF_MASK ) ) && ! ( cs -> interrupt_request & CPU_INTERRUPT_NMI ) ) {
 cs -> halted = 1 ;
 return EXCP_HLT ;
 }
 return 0 ;
 }