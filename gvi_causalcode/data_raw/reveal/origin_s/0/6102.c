static int pxa2xx_i2c_initfn ( SysBusDevice * dev ) {
 PXA2xxI2CState * s = FROM_SYSBUS ( PXA2xxI2CState , dev ) ;
 s -> bus = i2c_init_bus ( & dev -> qdev , "i2c" ) ;
 memory_region_init_io ( & s -> iomem , OBJECT ( s ) , & pxa2xx_i2c_ops , s , "pxa2xx-i2c" , s -> region_size ) ;
 sysbus_init_mmio ( dev , & s -> iomem ) ;
 sysbus_init_irq ( dev , & s -> irq ) ;
 return 0 ;
 }