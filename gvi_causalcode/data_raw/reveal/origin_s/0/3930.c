static int kvm_assign_irq_internal ( KVMState * s , uint32_t dev_id , uint32_t irq_type , uint32_t guest_irq ) {
 struct kvm_assigned_irq assigned_irq = {
 . assigned_dev_id = dev_id , . guest_irq = guest_irq , . flags = irq_type , }
 ;
 if ( kvm_check_extension ( s , KVM_CAP_ASSIGN_DEV_IRQ ) ) {
 return kvm_vm_ioctl ( s , KVM_ASSIGN_DEV_IRQ , & assigned_irq ) ;
 }
 else {
 return kvm_vm_ioctl ( s , KVM_ASSIGN_IRQ , & assigned_irq ) ;
 }
 }