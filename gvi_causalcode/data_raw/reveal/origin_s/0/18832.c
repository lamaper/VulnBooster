static void ram_class_init ( ObjectClass * klass , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 SysBusDeviceClass * k = SYS_BUS_DEVICE_CLASS ( klass ) ;
 k -> init = ram_init1 ;
 dc -> props = ram_properties ;
 }