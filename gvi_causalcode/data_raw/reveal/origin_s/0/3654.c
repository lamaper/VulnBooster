static void ecc_init ( hwaddr base , qemu_irq irq , uint32_t version ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "eccmemctl" ) ;
 qdev_prop_set_uint32 ( dev , "version" , version ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_connect_irq ( s , 0 , irq ) ;
 sysbus_mmio_map ( s , 0 , base ) ;
 if ( version == 0 ) {
 sysbus_mmio_map ( s , 1 , base + 0x1000 ) ;
 }
 }