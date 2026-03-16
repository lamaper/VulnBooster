static void prom_class_init ( ObjectClass * klass , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 SysBusDeviceClass * k = SYS_BUS_DEVICE_CLASS ( klass ) ;
 k -> init = prom_init1 ;
 dc -> props = prom_properties ;
 }