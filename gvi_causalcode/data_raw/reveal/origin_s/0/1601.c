static int arm_mptimer_init ( SysBusDevice * dev ) {
 ARMMPTimerState * s = FROM_SYSBUS ( ARMMPTimerState , dev ) ;
 int i ;
 if ( s -> num_cpu < 1 || s -> num_cpu > MAX_CPUS ) {
 hw_error ( "%s: num-cpu must be between 1 and %d\n" , __func__ , MAX_CPUS ) ;
 }
 memory_region_init_io ( & s -> iomem , OBJECT ( s ) , & arm_thistimer_ops , s , "arm_mptimer_timer" , 0x20 ) ;
 sysbus_init_mmio ( dev , & s -> iomem ) ;
 for ( i = 0 ;
 i < s -> num_cpu ;
 i ++ ) {
 TimerBlock * tb = & s -> timerblock [ i ] ;
 tb -> timer = qemu_new_timer_ns ( vm_clock , timerblock_tick , tb ) ;
 sysbus_init_irq ( dev , & tb -> irq ) ;
 memory_region_init_io ( & tb -> iomem , OBJECT ( s ) , & timerblock_ops , tb , "arm_mptimer_timerblock" , 0x20 ) ;
 sysbus_init_mmio ( dev , & tb -> iomem ) ;
 }
 return 0 ;
 }