static void arm_gic_realize ( DeviceState * dev , Error * * errp ) {
 int i ;
 GICState * s = ARM_GIC ( dev ) ;
 SysBusDevice * sbd = SYS_BUS_DEVICE ( dev ) ;
 ARMGICClass * agc = ARM_GIC_GET_CLASS ( s ) ;
 agc -> parent_realize ( dev , errp ) ;
 if ( error_is_set ( errp ) ) {
 return ;
 }
 gic_init_irqs_and_distributor ( s , s -> num_irq ) ;
 memory_region_init_io ( & s -> cpuiomem [ 0 ] , OBJECT ( s ) , & gic_thiscpu_ops , s , "gic_cpu" , 0x100 ) ;
 for ( i = 0 ;
 i < NUM_CPU ( s ) ;
 i ++ ) {
 s -> backref [ i ] = s ;
 memory_region_init_io ( & s -> cpuiomem [ i + 1 ] , OBJECT ( s ) , & gic_cpu_ops , & s -> backref [ i ] , "gic_cpu" , 0x100 ) ;
 }
 sysbus_init_mmio ( sbd , & s -> iomem ) ;
 for ( i = 0 ;
 i <= NUM_CPU ( s ) ;
 i ++ ) {
 sysbus_init_mmio ( sbd , & s -> cpuiomem [ i ] ) ;
 }
 }