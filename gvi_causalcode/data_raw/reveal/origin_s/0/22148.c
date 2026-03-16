bool kvm_has_adjust_clock_stable ( void ) {
 int ret = kvm_check_extension ( kvm_state , KVM_CAP_ADJUST_CLOCK ) ;
 return ( ret == KVM_CLOCK_TSC_STABLE ) ;
 }