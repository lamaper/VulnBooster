int kvm_device_intx_deassign ( KVMState * s , uint32_t dev_id , bool use_host_msi ) {
 return kvm_deassign_irq_internal ( s , dev_id , KVM_DEV_IRQ_GUEST_INTX | ( use_host_msi ? KVM_DEV_IRQ_HOST_MSI : KVM_DEV_IRQ_HOST_INTX ) ) ;
 }