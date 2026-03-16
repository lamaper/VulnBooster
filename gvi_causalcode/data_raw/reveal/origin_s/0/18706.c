int kvm_device_pci_deassign ( KVMState * s , uint32_t dev_id ) {
 struct kvm_assigned_pci_dev dev_data = {
 . assigned_dev_id = dev_id , }
 ;
 return kvm_vm_ioctl ( s , KVM_DEASSIGN_PCI_DEVICE , & dev_data ) ;
 }