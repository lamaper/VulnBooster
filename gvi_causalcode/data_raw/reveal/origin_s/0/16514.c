static void * sparc32_dma_init ( hwaddr daddr , qemu_irq parent_irq , void * iommu , qemu_irq * dev_irq , int is_ledma ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "sparc32_dma" ) ;
 qdev_prop_set_ptr ( dev , "iommu_opaque" , iommu ) ;
 qdev_prop_set_uint32 ( dev , "is_ledma" , is_ledma ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_connect_irq ( s , 0 , parent_irq ) ;
 * dev_irq = qdev_get_gpio_in ( dev , 0 ) ;
 sysbus_mmio_map ( s , 0 , daddr ) ;
 return s ;
 }