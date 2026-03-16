void kvm_arch_do_init_vcpu ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 if ( env -> mp_state == KVM_MP_STATE_UNINITIALIZED ) {
 env -> mp_state = KVM_MP_STATE_INIT_RECEIVED ;
 }
 }