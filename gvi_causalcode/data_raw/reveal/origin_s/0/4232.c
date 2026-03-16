static int kvm_put_one_msr ( X86CPU * cpu , int index , uint64_t value ) {
 kvm_msr_buf_reset ( cpu ) ;
 kvm_msr_entry_add ( cpu , index , value ) ;
 return kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_SET_MSRS , cpu -> kvm_msr_buf ) ;
 }