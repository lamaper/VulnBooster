static int virtio_net_exit_pci ( PCIDevice * pci_dev ) {
 VirtIOPCIProxy * proxy = DO_UPCAST ( VirtIOPCIProxy , pci_dev , pci_dev ) ;
 virtio_net_exit ( proxy -> vdev ) ;
 return virtio_exit_pci ( pci_dev ) ;
 }