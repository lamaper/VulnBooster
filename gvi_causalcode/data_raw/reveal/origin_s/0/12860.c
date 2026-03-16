static void idreg_class_init ( ObjectClass * klass , void * data ) {
 SysBusDeviceClass * k = SYS_BUS_DEVICE_CLASS ( klass ) ;
 k -> init = idreg_init1 ;
 }