int kvm_arch_add_msi_route_post ( struct kvm_irq_routing_entry * route , int vector , PCIDevice * dev ) {
 static bool notify_list_inited = false ;
 MSIRouteEntry * entry ;
 if ( ! dev ) {
 return 0 ;
 }
 entry = g_new0 ( MSIRouteEntry , 1 ) ;
 entry -> dev = dev ;
 entry -> vector = vector ;
 entry -> virq = route -> gsi ;
 QLIST_INSERT_HEAD ( & msi_route_list , entry , list ) ;
 trace_kvm_x86_add_msi_route ( route -> gsi ) ;
 if ( ! notify_list_inited ) {
 X86IOMMUState * iommu = x86_iommu_get_default ( ) ;
 if ( iommu ) {
 x86_iommu_iec_register_notifier ( iommu , kvm_update_msi_routes_all , NULL ) ;
 }
 notify_list_inited = true ;
 }
 return 0 ;
 }