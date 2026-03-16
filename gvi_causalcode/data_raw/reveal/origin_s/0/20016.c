static void * iommu_init ( hwaddr addr , uint32_t version , qemu_irq irq ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "iommu" ) ;
 qdev_prop_set_uint32 ( dev , "version" , version ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_connect_irq ( s , 0 , irq ) ;
 sysbus_mmio_map ( s , 0 , addr ) ;
 return s ;
 }