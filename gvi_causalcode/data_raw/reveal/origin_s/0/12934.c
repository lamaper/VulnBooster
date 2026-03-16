bool kvm_allows_irq0_override ( void ) {
 return ! kvm_irqchip_in_kernel ( ) || kvm_has_gsi_routing ( ) ;
 }