static void ram_init ( hwaddr addr , ram_addr_t RAM_size , uint64_t max_mem ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 RamDevice * d ;
 if ( ( uint64_t ) RAM_size > max_mem ) {
 fprintf ( stderr , "qemu: Too much memory for this machine: %d, maximum %d\n" , ( unsigned int ) ( RAM_size / ( 1024 * 1024 ) ) , ( unsigned int ) ( max_mem / ( 1024 * 1024 ) ) ) ;
 exit ( 1 ) ;
 }
 dev = qdev_create ( NULL , "memory" ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 d = FROM_SYSBUS ( RamDevice , s ) ;
 d -> size = RAM_size ;
 qdev_init_nofail ( dev ) ;
 sysbus_mmio_map ( s , 0 , addr ) ;
 }