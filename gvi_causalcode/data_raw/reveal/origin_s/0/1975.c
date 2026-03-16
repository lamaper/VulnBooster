static int virtio_blk_exit_pci ( PCIDevice * pci_dev ) {
 VirtIOPCIProxy * proxy = DO_UPCAST ( VirtIOPCIProxy , pci_dev , pci_dev ) ;
 drive_uninit ( proxy -> dinfo ) ;
 return virtio_exit_pci ( pci_dev ) ;
 }