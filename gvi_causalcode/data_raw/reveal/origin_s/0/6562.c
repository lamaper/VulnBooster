void qdev_init_nofail ( DeviceState * dev ) {
 DeviceInfo * info = dev -> info ;
 if ( qdev_init ( dev ) < 0 ) hw_error ( "Initialization of device %s failed\n" , info -> name ) ;
 }