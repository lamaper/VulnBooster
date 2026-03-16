static void virtio_pci_save_config ( void * opaque , QEMUFile * f ) {
 VirtIOPCIProxy * proxy = opaque ;
 pci_device_save ( & proxy -> pci_dev , f ) ;
 msix_save ( & proxy -> pci_dev , f ) ;
 if ( msix_present ( & proxy -> pci_dev ) ) qemu_put_be16 ( f , proxy -> vdev -> config_vector ) ;
 }