static void arm_mptimer_class_init ( ObjectClass * klass , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 SysBusDeviceClass * sbc = SYS_BUS_DEVICE_CLASS ( klass ) ;
 sbc -> init = arm_mptimer_init ;
 dc -> vmsd = & vmstate_arm_mptimer ;
 dc -> reset = arm_mptimer_reset ;
 dc -> no_user = 1 ;
 dc -> props = arm_mptimer_properties ;
 }