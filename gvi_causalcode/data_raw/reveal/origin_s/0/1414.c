bool kvm_has_smm ( void ) {
 return kvm_check_extension ( kvm_state , KVM_CAP_X86_SMM ) ;
 }