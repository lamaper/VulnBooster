static void usb_ehci_pci_finalize ( Object * obj ) {
 EHCIPCIState * i = PCI_EHCI ( obj ) ;
 EHCIState * s = & i -> ehci ;
 usb_ehci_finalize ( s ) ;
 }