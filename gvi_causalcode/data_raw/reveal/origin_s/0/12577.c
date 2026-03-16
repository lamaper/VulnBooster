static void virtio_pci_config_writel ( void * opaque , uint32_t addr , uint32_t val ) {
 VirtIOPCIProxy * proxy = opaque ;
 uint32_t config = VIRTIO_PCI_CONFIG ( & proxy -> pci_dev ) ;
 addr -= proxy -> addr ;
 if ( addr < config ) {
 virtio_ioport_write ( proxy , addr , val ) ;
 return ;
 }
 addr -= config ;
 virtio_config_writel ( proxy -> vdev , addr , val ) ;
 }