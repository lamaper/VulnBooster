static void apc_init ( hwaddr power_base , qemu_irq cpu_halt ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "apc" ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_mmio_map ( s , 0 , power_base ) ;
 sysbus_connect_irq ( s , 0 , cpu_halt ) ;
 }