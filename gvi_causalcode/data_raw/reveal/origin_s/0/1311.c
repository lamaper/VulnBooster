static int kvm_get_mce_cap_supported ( KVMState * s , uint64_t * mce_cap , int * max_banks ) {
 int r ;
 r = kvm_check_extension ( s , KVM_CAP_MCE ) ;
 if ( r > 0 ) {
 * max_banks = r ;
 return kvm_ioctl ( s , KVM_X86_GET_MCE_CAP_SUPPORTED , mce_cap ) ;
 }
 return - ENOSYS ;
 }