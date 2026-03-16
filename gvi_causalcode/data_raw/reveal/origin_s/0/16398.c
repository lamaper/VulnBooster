static int kvm_put_mp_state ( X86CPU * cpu ) {
 struct kvm_mp_state mp_state = {
 . mp_state = cpu -> env . mp_state }
 ;
 return kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_SET_MP_STATE , & mp_state ) ;
 }