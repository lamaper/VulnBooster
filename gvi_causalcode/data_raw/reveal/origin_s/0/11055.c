static int kvm_deassign_irq_internal ( KVMState * s , uint32_t dev_id , uint32_t type ) {
 struct kvm_assigned_irq assigned_irq = {
 . assigned_dev_id = dev_id , . flags = type , }
 ;
 return kvm_vm_ioctl ( s , KVM_DEASSIGN_DEV_IRQ , & assigned_irq ) ;
 }