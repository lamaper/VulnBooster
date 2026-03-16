static void idreg_init ( hwaddr addr ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "macio_idreg" ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_mmio_map ( s , 0 , addr ) ;
 cpu_physical_memory_write_rom ( addr , idreg_data , sizeof ( idreg_data ) ) ;
 }