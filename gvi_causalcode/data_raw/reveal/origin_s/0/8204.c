static void ehci_pci_register_types ( void ) {
 TypeInfo ehci_type_info = {
 . parent = TYPE_PCI_EHCI , . class_init = ehci_data_class_init , }
 ;
 int i ;
 type_register_static ( & ehci_pci_type_info ) ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( ehci_pci_info ) ;
 i ++ ) {
 ehci_type_info . name = ehci_pci_info [ i ] . name ;
 ehci_type_info . class_data = ehci_pci_info + i ;
 type_register ( & ehci_type_info ) ;
 }
 }