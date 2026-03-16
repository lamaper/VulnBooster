int kvm_device_msix_init_vectors ( KVMState * s , uint32_t dev_id , uint32_t nr_vectors ) {
 struct kvm_assigned_msix_nr msix_nr = {
 . assigned_dev_id = dev_id , . entry_nr = nr_vectors , }
 ;
 return kvm_vm_ioctl ( s , KVM_ASSIGN_SET_MSIX_NR , & msix_nr ) ;
 }