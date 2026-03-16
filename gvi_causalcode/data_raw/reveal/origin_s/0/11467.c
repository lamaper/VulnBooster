int kvm_device_msi_assign ( KVMState * s , uint32_t dev_id , int virq ) {
 return kvm_assign_irq_internal ( s , dev_id , KVM_DEV_IRQ_HOST_MSI | KVM_DEV_IRQ_GUEST_MSI , virq ) ;
 }