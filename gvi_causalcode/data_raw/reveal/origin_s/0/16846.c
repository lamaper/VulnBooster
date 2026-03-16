type_init ( ehci_pci_register_types ) struct ehci_companions {
 const char * name ;
 int func ;
 int port ;
 }
 ;
 static const struct ehci_companions ich9_1d [ ] = {
 {
 . name = "ich9-usb-uhci1" , . func = 0 , . port = 0 }
 , {
 . name = "ich9-usb-uhci2" , . func = 1 , . port = 2 }
 , {
 . name = "ich9-usb-uhci3" , . func = 2 , . port = 4 }
 , }