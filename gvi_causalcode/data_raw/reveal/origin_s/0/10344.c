int kvm_device_msi_deassign ( KVMState * s , uint32_t dev_id ) {
 return kvm_deassign_irq_internal ( s , dev_id , KVM_DEV_IRQ_GUEST_MSI | KVM_DEV_IRQ_HOST_MSI ) ;
 }