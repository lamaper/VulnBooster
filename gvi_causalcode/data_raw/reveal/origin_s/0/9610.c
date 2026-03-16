static int ram_init1 ( SysBusDevice * dev ) {
 RamDevice * d = FROM_SYSBUS ( RamDevice , dev ) ;
 memory_region_init_ram ( & d -> ram , OBJECT ( d ) , "sun4m.ram" , d -> size ) ;
 vmstate_register_ram_global ( & d -> ram ) ;
 sysbus_init_mmio ( dev , & d -> ram ) ;
 return 0 ;
 }