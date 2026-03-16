static void lance_init ( NICInfo * nd , hwaddr leaddr , void * dma_opaque , qemu_irq irq ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 qemu_irq reset ;
 qemu_check_nic_model ( & nd_table [ 0 ] , "lance" ) ;
 dev = qdev_create ( NULL , "lance" ) ;
 qdev_set_nic_properties ( dev , nd ) ;
 qdev_prop_set_ptr ( dev , "dma" , dma_opaque ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_mmio_map ( s , 0 , leaddr ) ;
 sysbus_connect_irq ( s , 0 , irq ) ;
 reset = qdev_get_gpio_in ( dev , 0 ) ;
 qdev_connect_gpio_out ( dma_opaque , 0 , reset ) ;
 }