static int virtio_exit_pci ( PCIDevice * pci_dev ) {
 return msix_uninit ( pci_dev ) ;
 }