int ehci_create_ich9_with_companions ( PCIBus * bus , int slot ) {
 const struct ehci_companions * comp ;
 PCIDevice * ehci , * uhci ;
 BusState * usbbus ;
 const char * name ;
 int i ;
 switch ( slot ) {
 case 0x1d : name = "ich9-usb-ehci1" ;
 comp = ich9_1d ;
 break ;
 case 0x1a : name = "ich9-usb-ehci2" ;
 comp = ich9_1a ;
 break ;
 default : return - 1 ;
 }
 ehci = pci_create_multifunction ( bus , PCI_DEVFN ( slot , 7 ) , true , name ) ;
 qdev_init_nofail ( & ehci -> qdev ) ;
 usbbus = QLIST_FIRST ( & ehci -> qdev . child_bus ) ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) {
 uhci = pci_create_multifunction ( bus , PCI_DEVFN ( slot , comp [ i ] . func ) , true , comp [ i ] . name ) ;
 qdev_prop_set_string ( & uhci -> qdev , "masterbus" , usbbus -> name ) ;
 qdev_prop_set_uint32 ( & uhci -> qdev , "firstport" , comp [ i ] . port ) ;
 qdev_init_nofail ( & uhci -> qdev ) ;
 }
 return 0 ;
 }