static int virtio_pci_load_queue ( void * opaque , int n , QEMUFile * f ) {
 VirtIOPCIProxy * proxy = opaque ;
 uint16_t vector ;
 if ( msix_present ( & proxy -> pci_dev ) ) {
 qemu_get_be16s ( f , & vector ) ;
 }
 else {
 vector = VIRTIO_NO_VECTOR ;
 }
 virtio_queue_set_vector ( proxy -> vdev , n , vector ) ;
 if ( vector != VIRTIO_NO_VECTOR ) {
 return msix_vector_use ( & proxy -> pci_dev , vector ) ;
 }
 return 0 ;
 }