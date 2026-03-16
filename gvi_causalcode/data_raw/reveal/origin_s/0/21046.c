static void virtio_pci_save_queue ( void * opaque , int n , QEMUFile * f ) {
 VirtIOPCIProxy * proxy = opaque ;
 if ( msix_present ( & proxy -> pci_dev ) ) qemu_put_be16 ( f , virtio_queue_vector ( proxy -> vdev , n ) ) ;
 }