static void kvm_update_msi_routes_all ( void * private , bool global , uint32_t index , uint32_t mask ) {
 int cnt = 0 ;
 MSIRouteEntry * entry ;
 MSIMessage msg ;
 PCIDevice * dev ;
 QLIST_FOREACH ( entry , & msi_route_list , list ) {
 cnt ++ ;
 dev = entry -> dev ;
 if ( ! msix_enabled ( dev ) && ! msi_enabled ( dev ) ) {
 continue ;
 }
 msg = pci_get_msi_message ( dev , entry -> vector ) ;
 kvm_irqchip_update_msi_route ( kvm_state , entry -> virq , msg , dev ) ;
 }
 kvm_irqchip_commit_routes ( kvm_state ) ;
 trace_kvm_x86_update_msi_routes ( cnt ) ;
 }