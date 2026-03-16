static void ehci_class_init ( ObjectClass * klass , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 PCIDeviceClass * k = PCI_DEVICE_CLASS ( klass ) ;
 k -> realize = usb_ehci_pci_realize ;
 k -> exit = usb_ehci_pci_exit ;
 k -> class_id = PCI_CLASS_SERIAL_USB ;
 k -> config_write = usb_ehci_pci_write_config ;
 dc -> vmsd = & vmstate_ehci_pci ;
 dc -> props = ehci_pci_properties ;
 dc -> reset = usb_ehci_pci_reset ;
 }