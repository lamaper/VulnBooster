static void usb_ehci_pci_exit ( PCIDevice * dev ) {
 EHCIPCIState * i = PCI_EHCI ( dev ) ;
 EHCIState * s = & i -> ehci ;
 usb_ehci_unrealize ( s , DEVICE ( dev ) , NULL ) ;
 g_free ( s -> irq ) ;
 s -> irq = NULL ;
 }