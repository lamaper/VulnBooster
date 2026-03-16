static void ehci_data_class_init ( ObjectClass * klass , void * data ) {
 PCIDeviceClass * k = PCI_DEVICE_CLASS ( klass ) ;
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 EHCIPCIInfo * i = data ;
 k -> vendor_id = i -> vendor_id ;
 k -> device_id = i -> device_id ;
 k -> revision = i -> revision ;
 set_bit ( DEVICE_CATEGORY_USB , dc -> categories ) ;
 if ( i -> companion ) {
 dc -> hotpluggable = false ;
 }
 }