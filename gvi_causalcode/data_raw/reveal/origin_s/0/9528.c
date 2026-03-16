static void usb_ehci_pci_reset ( DeviceState * dev ) {
 PCIDevice * pci_dev = PCI_DEVICE ( dev ) ;
 EHCIPCIState * i = PCI_EHCI ( pci_dev ) ;
 EHCIState * s = & i -> ehci ;
 ehci_reset ( s ) ;
 }