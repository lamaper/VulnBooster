static DeviceState * slavio_intctl_init ( hwaddr addr , hwaddr addrg , qemu_irq * * parent_irq ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 unsigned int i , j ;
 dev = qdev_create ( NULL , "slavio_intctl" ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 for ( i = 0 ;
 i < MAX_CPUS ;
 i ++ ) {
 for ( j = 0 ;
 j < MAX_PILS ;
 j ++ ) {
 sysbus_connect_irq ( s , i * MAX_PILS + j , parent_irq [ i ] [ j ] ) ;
 }
 }
 sysbus_mmio_map ( s , 0 , addrg ) ;
 for ( i = 0 ;
 i < MAX_CPUS ;
 i ++ ) {
 sysbus_mmio_map ( s , i + 1 , addr + i * TARGET_PAGE_SIZE ) ;
 }
 return dev ;
 }