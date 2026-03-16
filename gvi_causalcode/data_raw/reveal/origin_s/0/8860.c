static void s390_virtio_bus_register_withprop ( VirtIOS390DeviceInfo * info ) {
 info -> qdev . init = s390_virtio_busdev_init ;
 info -> qdev . bus_info = & s390_virtio_bus_info ;
 assert ( info -> qdev . size >= sizeof ( VirtIOS390Device ) ) ;
 qdev_register ( & info -> qdev ) ;
 }