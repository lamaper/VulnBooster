static int s390_virtio_busdev_init ( DeviceState * dev , DeviceInfo * info ) {
 VirtIOS390DeviceInfo * _info = ( VirtIOS390DeviceInfo * ) info ;
 VirtIOS390Device * _dev = ( VirtIOS390Device * ) dev ;
 return _info -> init ( _dev ) ;
 }