int kvm_device_msix_assign ( KVMState * s , uint32_t dev_id ) {
 return kvm_assign_irq_internal ( s , dev_id , KVM_DEV_IRQ_HOST_MSIX | KVM_DEV_IRQ_GUEST_MSIX , 0 ) ;
 }