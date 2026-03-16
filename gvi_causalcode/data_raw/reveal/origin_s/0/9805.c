static int pxa2xx_ssp_init ( SysBusDevice * dev ) {
 PXA2xxSSPState * s = FROM_SYSBUS ( PXA2xxSSPState , dev ) ;
 sysbus_init_irq ( dev , & s -> irq ) ;
 memory_region_init_io ( & s -> iomem , OBJECT ( s ) , & pxa2xx_ssp_ops , s , "pxa2xx-ssp" , 0x1000 ) ;
 sysbus_init_mmio ( dev , & s -> iomem ) ;
 register_savevm ( & dev -> qdev , "pxa2xx_ssp" , - 1 , 0 , pxa2xx_ssp_save , pxa2xx_ssp_load , s ) ;
 s -> bus = ssi_create_bus ( & dev -> qdev , "ssi" ) ;
 return 0 ;
 }