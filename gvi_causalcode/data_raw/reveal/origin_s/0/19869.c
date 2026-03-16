static void afx_init ( hwaddr addr ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 dev = qdev_create ( NULL , "tcx_afx" ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_mmio_map ( s , 0 , addr ) ;
 }