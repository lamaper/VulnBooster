int kvm_arch_fixup_msi_route ( struct kvm_irq_routing_entry * route , uint64_t address , uint32_t data , PCIDevice * dev ) {
 X86IOMMUState * iommu = x86_iommu_get_default ( ) ;
 if ( iommu ) {
 int ret ;
 MSIMessage src , dst ;
 X86IOMMUClass * class = X86_IOMMU_GET_CLASS ( iommu ) ;
 src . address = route -> u . msi . address_hi ;
 src . address <<= VTD_MSI_ADDR_HI_SHIFT ;
 src . address |= route -> u . msi . address_lo ;
 src . data = route -> u . msi . data ;
 ret = class -> int_remap ( iommu , & src , & dst , dev ? pci_requester_id ( dev ) : X86_IOMMU_SID_INVALID ) ;
 if ( ret ) {
 trace_kvm_x86_fixup_msi_error ( route -> gsi ) ;
 return 1 ;
 }
 route -> u . msi . address_hi = dst . address >> VTD_MSI_ADDR_HI_SHIFT ;
 route -> u . msi . address_lo = dst . address & VTD_MSI_ADDR_LO_MASK ;
 route -> u . msi . data = dst . data ;
 }
 return 0 ;
 }