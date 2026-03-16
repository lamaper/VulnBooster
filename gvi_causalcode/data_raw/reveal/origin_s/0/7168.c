static void slavio_misc_init ( hwaddr base , hwaddr aux1_base , hwaddr aux2_base , qemu_irq irq , qemu_irq fdc_tc ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "slavio_misc" ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 if ( base ) {
 sysbus_mmio_map ( s , 0 , base + MISC_CFG ) ;
 sysbus_mmio_map ( s , 1 , base + MISC_DIAG ) ;
 sysbus_mmio_map ( s , 2 , base + MISC_MDM ) ;
 sysbus_mmio_map ( s , 3 , base + MISC_LEDS ) ;
 sysbus_mmio_map ( s , 4 , base + MISC_SYS ) ;
 }
 if ( aux1_base ) {
 sysbus_mmio_map ( s , 5 , aux1_base ) ;
 }
 if ( aux2_base ) {
 sysbus_mmio_map ( s , 6 , aux2_base ) ;
 }
 sysbus_connect_irq ( s , 0 , irq ) ;
 sysbus_connect_irq ( s , 1 , fdc_tc ) ;
 slavio_system_powerdown = qdev_get_gpio_in ( dev , 0 ) ;
 qemu_register_powerdown_notifier ( & slavio_system_powerdown_notifier ) ;
 }