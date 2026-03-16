static uint32_t virtio_pci_config_readb ( void * opaque , uint32_t addr ) {
 VirtIOPCIProxy * proxy = opaque ;
 uint32_t config = VIRTIO_PCI_CONFIG ( & proxy -> pci_dev ) ;
 addr -= proxy -> addr ;
 if ( addr < config ) return virtio_ioport_read ( proxy , addr ) ;
 addr -= config ;
 return virtio_config_readb ( proxy -> vdev , addr ) ;
 }