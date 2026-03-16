static void virtio_map ( PCIDevice * pci_dev , int region_num , pcibus_t addr , pcibus_t size , int type ) {
 VirtIOPCIProxy * proxy = container_of ( pci_dev , VirtIOPCIProxy , pci_dev ) ;
 VirtIODevice * vdev = proxy -> vdev ;
 unsigned config_len = VIRTIO_PCI_REGION_SIZE ( pci_dev ) + vdev -> config_len ;
 proxy -> addr = addr ;
 register_ioport_write ( addr , config_len , 1 , virtio_pci_config_writeb , proxy ) ;
 register_ioport_write ( addr , config_len , 2 , virtio_pci_config_writew , proxy ) ;
 register_ioport_write ( addr , config_len , 4 , virtio_pci_config_writel , proxy ) ;
 register_ioport_read ( addr , config_len , 1 , virtio_pci_config_readb , proxy ) ;
 register_ioport_read ( addr , config_len , 2 , virtio_pci_config_readw , proxy ) ;
 register_ioport_read ( addr , config_len , 4 , virtio_pci_config_readl , proxy ) ;
 if ( vdev -> config_len ) vdev -> get_config ( vdev , vdev -> config ) ;
 }