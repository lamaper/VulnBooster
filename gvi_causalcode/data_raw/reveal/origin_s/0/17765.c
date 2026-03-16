static void openpic_class_init ( ObjectClass * oc , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( oc ) ;
 dc -> realize = openpic_realize ;
 dc -> props = openpic_properties ;
 dc -> reset = openpic_reset ;
 }