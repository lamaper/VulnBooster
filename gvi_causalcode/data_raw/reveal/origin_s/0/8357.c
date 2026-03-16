static void macio_ide_class_init ( ObjectClass * oc , void * data ) {
 DeviceClass * dc = DEVICE_CLASS ( oc ) ;
 dc -> realize = macio_ide_realizefn ;
 dc -> reset = macio_ide_reset ;
 dc -> vmsd = & vmstate_pmac ;
 }