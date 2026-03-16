int kvm_device_intx_set_mask ( KVMState * s , uint32_t dev_id , bool masked ) {
 struct kvm_assigned_pci_dev dev_data = {
 . assigned_dev_id = dev_id , . flags = masked ? KVM_DEV_ASSIGN_MASK_INTX : 0 , }
 ;
 return kvm_vm_ioctl ( s , KVM_ASSIGN_SET_INTX_MASK , & dev_data ) ;
 }