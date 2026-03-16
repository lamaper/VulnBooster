static void mpc8544_guts_initfn ( Object * obj ) {
 SysBusDevice * d = SYS_BUS_DEVICE ( obj ) ;
 GutsState * s = MPC8544_GUTS ( obj ) ;
 memory_region_init_io ( & s -> iomem , OBJECT ( s ) , & mpc8544_guts_ops , s , "mpc8544.guts" , MPC8544_GUTS_MMIO_SIZE ) ;
 sysbus_init_mmio ( d , & s -> iomem ) ;
 }