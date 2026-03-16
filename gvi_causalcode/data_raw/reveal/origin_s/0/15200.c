void gic_init_irqs_and_distributor ( GICState * s , int num_irq ) {
 int i ;
 i = s -> num_irq - GIC_INTERNAL ;
 if ( s -> revision != REV_NVIC ) {
 i += ( GIC_INTERNAL * s -> num_cpu ) ;
 }
 qdev_init_gpio_in ( & s -> busdev . qdev , gic_set_irq , i ) ;
 for ( i = 0 ;
 i < NUM_CPU ( s ) ;
 i ++ ) {
 sysbus_init_irq ( & s -> busdev , & s -> parent_irq [ i ] ) ;
 }
 memory_region_init_io ( & s -> iomem , OBJECT ( s ) , & gic_dist_ops , s , "gic_dist" , 0x1000 ) ;
 }