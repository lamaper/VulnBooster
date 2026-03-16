static void armv7m_nvic_class_init ( ObjectClass * klass , void * data ) {
 NVICClass * nc = NVIC_CLASS ( klass ) ;
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 nc -> parent_reset = dc -> reset ;
 nc -> parent_realize = dc -> realize ;
 dc -> vmsd = & vmstate_nvic ;
 dc -> reset = armv7m_nvic_reset ;
 dc -> realize = armv7m_nvic_realize ;
 }