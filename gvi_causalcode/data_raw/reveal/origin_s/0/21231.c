PXA2xxI2CState * pxa2xx_i2c_init ( hwaddr base , qemu_irq irq , uint32_t region_size ) {
 DeviceState * dev ;
 SysBusDevice * i2c_dev ;
 PXA2xxI2CState * s ;
 i2c_dev = SYS_BUS_DEVICE ( qdev_create ( NULL , "pxa2xx_i2c" ) ) ;
 qdev_prop_set_uint32 ( & i2c_dev -> qdev , "size" , region_size + 1 ) ;
 qdev_prop_set_uint32 ( & i2c_dev -> qdev , "offset" , base & region_size ) ;
 qdev_init_nofail ( & i2c_dev -> qdev ) ;
 sysbus_mmio_map ( i2c_dev , 0 , base & ~ region_size ) ;
 sysbus_connect_irq ( i2c_dev , 0 , irq ) ;
 s = FROM_SYSBUS ( PXA2xxI2CState , i2c_dev ) ;
 dev = i2c_create_slave ( i2c_init_bus ( NULL , "dummy" ) , "pxa2xx-i2c-slave" , 0 ) ;
 s -> slave = FROM_I2C_SLAVE ( PXA2xxI2CSlaveState , I2C_SLAVE ( dev ) ) ;
 s -> slave -> host = s ;
 return s ;
 }