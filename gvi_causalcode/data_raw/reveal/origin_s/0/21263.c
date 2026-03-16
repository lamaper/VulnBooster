static void audio_init ( PCIBus * pci_bus ) {
 vt82c686b_ac97_init ( pci_bus , PCI_DEVFN ( FULONG2E_VIA_SLOT , 5 ) ) ;
 vt82c686b_mc97_init ( pci_bus , PCI_DEVFN ( FULONG2E_VIA_SLOT , 6 ) ) ;
 }