static unsigned virtio_pci_get_features ( void * opaque ) {
 VirtIOPCIProxy * proxy = opaque ;
 return proxy -> host_features ;
 }