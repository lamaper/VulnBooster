static void virtio_ioport_write ( void * opaque , uint32_t addr , uint32_t val ) {
 VirtIOPCIProxy * proxy = opaque ;
 VirtIODevice * vdev = proxy -> vdev ;
 target_phys_addr_t pa ;
 switch ( addr ) {
 case VIRTIO_PCI_GUEST_FEATURES : if ( val & ( 1 << VIRTIO_F_BAD_FEATURE ) ) {
 if ( vdev -> bad_features ) val = proxy -> host_features & vdev -> bad_features ( vdev ) ;
 else val = 0 ;
 }
 if ( vdev -> set_features ) vdev -> set_features ( vdev , val ) ;
 vdev -> guest_features = val ;
 break ;
 case VIRTIO_PCI_QUEUE_PFN : pa = ( target_phys_addr_t ) val << VIRTIO_PCI_QUEUE_ADDR_SHIFT ;
 if ( pa == 0 ) {
 virtio_reset ( proxy -> vdev ) ;
 msix_unuse_all_vectors ( & proxy -> pci_dev ) ;
 }
 else virtio_queue_set_addr ( vdev , vdev -> queue_sel , pa ) ;
 break ;
 case VIRTIO_PCI_QUEUE_SEL : if ( val < VIRTIO_PCI_QUEUE_MAX ) vdev -> queue_sel = val ;
 break ;
 case VIRTIO_PCI_QUEUE_NOTIFY : virtio_queue_notify ( vdev , val ) ;
 break ;
 case VIRTIO_PCI_STATUS : vdev -> status = val & 0xFF ;
 if ( vdev -> status == 0 ) {
 virtio_reset ( proxy -> vdev ) ;
 msix_unuse_all_vectors ( & proxy -> pci_dev ) ;
 }
 break ;
 case VIRTIO_MSI_CONFIG_VECTOR : msix_vector_unuse ( & proxy -> pci_dev , vdev -> config_vector ) ;
 if ( msix_vector_use ( & proxy -> pci_dev , val ) < 0 ) val = VIRTIO_NO_VECTOR ;
 vdev -> config_vector = val ;
 break ;
 case VIRTIO_MSI_QUEUE_VECTOR : msix_vector_unuse ( & proxy -> pci_dev , virtio_queue_vector ( vdev , vdev -> queue_sel ) ) ;
 if ( msix_vector_use ( & proxy -> pci_dev , val ) < 0 ) val = VIRTIO_NO_VECTOR ;
 virtio_queue_set_vector ( vdev , vdev -> queue_sel , val ) ;
 break ;
 default : fprintf ( stderr , "%s: unexpected address 0x%x value 0x%x\n" , __func__ , addr , val ) ;
 break ;
 }
 }