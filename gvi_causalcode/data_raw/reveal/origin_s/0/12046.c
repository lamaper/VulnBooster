int kvm_device_intx_assign ( KVMState * s , uint32_t dev_id , bool use_host_msi , uint32_t guest_irq ) {
 uint32_t irq_type = KVM_DEV_IRQ_GUEST_INTX | ( use_host_msi ? KVM_DEV_IRQ_HOST_MSI : KVM_DEV_IRQ_HOST_INTX ) ;
 return kvm_assign_irq_internal ( s , dev_id , irq_type , guest_irq ) ;
 }