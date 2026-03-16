int qdev_simple_unplug_cb ( DeviceState * dev ) {
 qdev_free ( dev ) ;
 return 0 ;
 }