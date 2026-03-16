static void armv7m_nvic_realize ( DeviceState * dev , Error * * errp ) {
 nvic_state * s = NVIC ( dev ) ;
 NVICClass * nc = NVIC_GET_CLASS ( s ) ;
 s -> gic . num_cpu = 1 ;
 s -> gic . revision = 0xffffffff ;
 s -> num_irq = s -> gic . num_irq ;
 nc -> parent_realize ( dev , errp ) ;
 if ( error_is_set ( errp ) ) {
 return ;
 }
 gic_init_irqs_and_distributor ( & s -> gic , s -> num_irq ) ;
 memory_region_init ( & s -> container , OBJECT ( s ) , "nvic" , 0x1000 ) ;
 memory_region_init_io ( & s -> sysregmem , OBJECT ( s ) , & nvic_sysreg_ops , s , "nvic_sysregs" , 0x1000 ) ;
 memory_region_add_subregion ( & s -> container , 0 , & s -> sysregmem ) ;
 memory_region_init_alias ( & s -> gic_iomem_alias , OBJECT ( s ) , "nvic-gic" , & s -> gic . iomem , 0x100 , 0xc00 ) ;
 memory_region_add_subregion_overlap ( & s -> container , 0x100 , & s -> gic_iomem_alias , 1 ) ;
 memory_region_add_subregion ( get_system_memory ( ) , 0xe000e000 , & s -> container ) ;
 s -> systick . timer = qemu_new_timer_ns ( vm_clock , systick_timer_tick , s ) ;
 }