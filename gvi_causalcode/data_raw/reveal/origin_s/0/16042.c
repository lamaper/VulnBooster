int kvm_device_msix_set_vector ( KVMState * s , uint32_t dev_id , uint32_t vector , int virq ) {
 struct kvm_assigned_msix_entry msix_entry = {
 . assigned_dev_id = dev_id , . gsi = virq , . entry = vector , }
 ;
 return kvm_vm_ioctl ( s , KVM_ASSIGN_SET_MSIX_ENTRY , & msix_entry ) ;
 }