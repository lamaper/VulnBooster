static int virtio_pci_load_config ( void * opaque , QEMUFile * f ) {
 VirtIOPCIProxy * proxy = opaque ;
 int ret ;
 ret = pci_device_load ( & proxy -> pci_dev , f ) ;
 if ( ret ) {
 return ret ;
 }
 msix_load ( & proxy -> pci_dev , f ) ;
 if ( msix_present ( & proxy -> pci_dev ) ) {
 qemu_get_be16s ( f , & proxy -> vdev -> config_vector ) ;
 }
 else {
 proxy -> vdev -> config_vector = VIRTIO_NO_VECTOR ;
 }
 if ( proxy -> vdev -> config_vector != VIRTIO_NO_VECTOR ) {
 return msix_vector_use ( & proxy -> pci_dev , proxy -> vdev -> config_vector ) ;
 }
 return 0 ;
 }