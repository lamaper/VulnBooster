static int kvm_get_apic ( X86CPU * cpu ) {
 DeviceState * apic = cpu -> apic_state ;
 struct kvm_lapic_state kapic ;
 int ret ;
 if ( apic && kvm_irqchip_in_kernel ( ) ) {
 ret = kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_GET_LAPIC , & kapic ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 kvm_get_apic_state ( apic , & kapic ) ;
 }
 return 0 ;
 }