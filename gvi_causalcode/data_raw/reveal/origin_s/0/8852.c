bool kvm_device_msix_supported ( KVMState * s ) {
 return kvm_vm_ioctl ( s , KVM_ASSIGN_SET_MSIX_NR , NULL ) == - EFAULT ;
 }