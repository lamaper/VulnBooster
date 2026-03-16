void kvm_arch_init_irq_routing ( KVMState * s ) {
 if ( ! kvm_check_extension ( s , KVM_CAP_IRQ_ROUTING ) ) {
 no_hpet = 1 ;
 }
 kvm_msi_via_irqfd_allowed = true ;
 kvm_gsi_routing_allowed = true ;
 if ( kvm_irqchip_is_split ( ) ) {
 int i ;
 for ( i = 0 ;
 i < IOAPIC_NUM_PINS ;
 i ++ ) {
 if ( kvm_irqchip_add_msi_route ( s , 0 , NULL ) < 0 ) {
 error_report ( "Could not enable split IRQ mode." ) ;
 exit ( 1 ) ;
 }
 }
 }
 }