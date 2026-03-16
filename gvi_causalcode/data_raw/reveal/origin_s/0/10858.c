static void vapic_class_init ( ObjectClass * klass , void * data ) {
 SysBusDeviceClass * sc = SYS_BUS_DEVICE_CLASS ( klass ) ;
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 dc -> no_user = 1 ;
 dc -> reset = vapic_reset ;
 dc -> vmsd = & vmstate_vapic ;
 sc -> init = vapic_init ;
 }