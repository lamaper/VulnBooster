static void usb_ehci_pci_write_config ( PCIDevice * dev , uint32_t addr , uint32_t val , int l ) {
 EHCIPCIState * i = PCI_EHCI ( dev ) ;
 bool busmaster ;
 pci_default_write_config ( dev , addr , val , l ) ;
 if ( ! range_covers_byte ( addr , l , PCI_COMMAND ) ) {
 return ;
 }
 busmaster = pci_get_word ( dev -> config + PCI_COMMAND ) & PCI_COMMAND_MASTER ;
 i -> ehci . as = busmaster ? pci_get_address_space ( dev ) : & address_space_memory ;
 }