int kvm_device_pci_assign ( KVMState * s , PCIHostDeviceAddress * dev_addr , uint32_t flags , uint32_t * dev_id ) {
 struct kvm_assigned_pci_dev dev_data = {
 . segnr = dev_addr -> domain , . busnr = dev_addr -> bus , . devfn = PCI_DEVFN ( dev_addr -> slot , dev_addr -> function ) , . flags = flags , }
 ;
 int ret ;
 dev_data . assigned_dev_id = ( dev_addr -> domain << 16 ) | ( dev_addr -> bus << 8 ) | dev_data . devfn ;
 ret = kvm_vm_ioctl ( s , KVM_ASSIGN_PCI_DEVICE , & dev_data ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 * dev_id = dev_data . assigned_dev_id ;
 return 0 ;
 }