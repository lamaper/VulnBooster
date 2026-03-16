static void virtio_pci_notify ( void * opaque , uint16_t vector ) {
 VirtIOPCIProxy * proxy = opaque ;
 if ( msix_enabled ( & proxy -> pci_dev ) ) msix_notify ( & proxy -> pci_dev , vector ) ;
 else qemu_set_irq ( proxy -> pci_dev . irq [ 0 ] , proxy -> vdev -> isr & 1 ) ;
 }