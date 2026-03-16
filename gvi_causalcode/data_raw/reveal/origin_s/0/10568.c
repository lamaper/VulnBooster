static int kvm_guest_debug_workarounds ( X86CPU * cpu ) {
 CPUState * cs = CPU ( cpu ) ;
 CPUX86State * env = & cpu -> env ;
 int ret = 0 ;
 unsigned long reinject_trap = 0 ;
 if ( ! kvm_has_vcpu_events ( ) ) {
 if ( env -> exception_injected == 1 ) {
 reinject_trap = KVM_GUESTDBG_INJECT_DB ;
 }
 else if ( env -> exception_injected == 3 ) {
 reinject_trap = KVM_GUESTDBG_INJECT_BP ;
 }
 env -> exception_injected = - 1 ;
 }
 if ( reinject_trap || ( ! kvm_has_robust_singlestep ( ) && cs -> singlestep_enabled ) ) {
 ret = kvm_update_guest_debug ( cs , reinject_trap ) ;
 }
 return ret ;
 }