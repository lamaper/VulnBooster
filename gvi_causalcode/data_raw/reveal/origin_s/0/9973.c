static int kvm_get_mp_state ( X86CPU * cpu ) {
 CPUState * cs = CPU ( cpu ) ;
 CPUX86State * env = & cpu -> env ;
 struct kvm_mp_state mp_state ;
 int ret ;
 ret = kvm_vcpu_ioctl ( cs , KVM_GET_MP_STATE , & mp_state ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 env -> mp_state = mp_state . mp_state ;
 if ( kvm_irqchip_in_kernel ( ) ) {
 cs -> halted = ( mp_state . mp_state == KVM_MP_STATE_HALTED ) ;
 }
 return 0 ;
 }