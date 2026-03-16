static void macio_ide_initfn ( Object * obj ) {
 SysBusDevice * d = SYS_BUS_DEVICE ( obj ) ;
 MACIOIDEState * s = MACIO_IDE ( obj ) ;
 ide_bus_new ( & s -> bus , sizeof ( s -> bus ) , DEVICE ( obj ) , 0 , 2 ) ;
 memory_region_init_io ( & s -> mem , obj , & pmac_ide_ops , s , "pmac-ide" , 0x1000 ) ;
 sysbus_init_mmio ( d , & s -> mem ) ;
 sysbus_init_irq ( d , & s -> irq ) ;
 sysbus_init_irq ( d , & s -> dma_irq ) ;
 }