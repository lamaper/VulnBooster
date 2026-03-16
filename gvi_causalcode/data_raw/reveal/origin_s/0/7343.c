static void arm_gic_class_init ( ObjectClass * klass , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( klass ) ;
 ARMGICClass * agc = ARM_GIC_CLASS ( klass ) ;
 dc -> no_user = 1 ;
 agc -> parent_realize = dc -> realize ;
 dc -> realize = arm_gic_realize ;
 }